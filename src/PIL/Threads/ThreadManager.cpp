#include <Parallax/Threads/ThreadManager.hpp>

#include <Parallax/Threads/Pipe.hpp>
#include <Parallax/Debug/Debug.hpp>
#include <Parallax/Defines.hpp>

#include <condition_variable>
#include <thread>
#include <atomic>

namespace Parallax::Threads::Manager
{
    struct ThreadArgs
	{
		uint32_t		threadNum;
	};

    static const uint32_t SPIN_COUNT                 = 100;
    static const uint32_t SPIN_BACKOFF_MULTIPLIER    = 10;
    static const uint32_t MAX_NUM_INITIAL_PARTITIONS = 8;

	static U32                     s_NumThreads(0);
	static ThreadArgs*             s_pThreadNumStore(nullptr);
	static std::thread**           s_pThreads(nullptr);
	static std::atomic<I32>        s_bRunning(0);
	static std::atomic<I32>        s_NumThreadsRunning(0);
	static std::atomic<I32>        s_NumThreadsWaiting(0);
	static U32                     s_NumPartitions(0);
	static std::condition_variable s_NewTaskEvent;
	static std::mutex              s_NewTaskEventMutex;
	static U32                     s_NumInitialPartitions(0);
	static bool                    s_bHaveThreads(false);

// thread_local not well supported yet by C++11 compilers.
#ifdef _MSC_VER
    #if _MSC_VER <= 1800
        #define thread_local __declspec(thread)
    #endif
#elif __APPLE__
        // Apple thread_local currently not implemented despite it being in Clang.
        #define thread_local __thread
#endif

    static thread_local uint32_t   gtl_threadNum = 0;

    inline void Pause()
    {
        #if defined _WIN32 && defined _M_X86
    		_mm_pause();
    	#elif defined __i386__
    		asm("pause");
    	#else
    	#endif
    }

    static void WakeThreads()
    {
        if (s_NumThreadsWaiting.load(std::memory_order_relaxed))
        {
            s_NewTaskEvent.notify_all();
        }
    }

    static SubTask SplitTask(SubTask& subTask, U32 rangeToSplit)
    {
        SubTask splitTask = subTask;
        U32 rangeLeft = subTask.partition.end - subTask.partition.start;

        if (rangeToSplit > rangeLeft)
        {
            rangeToSplit = rangeLeft;
        }
        splitTask.partition.end = subTask.partition.start + rangeToSplit;
        subTask.partition.start = splitTask.partition.end;

        return splitTask;
    }

    static void SplitAndAddTask(U32 threadNum, SubTask subTask, U32 rangeToSplit, I32 runningCountOffset)
    {
        I32 numAdded = 0;
        while (subTask.partition.start != subTask.partition.end)
        {
            SubTask taskToAdd = SplitTask(subTask, rangeToSplit);

            // Add the partition to the pipe
            ++numAdded;
            if (!Pipes::WriterTryWriteFront(taskToAdd, gtl_threadNum))
            {
                if (numAdded > 1)
                {
                    WakeThreads();
                }

                // Alter range to run the appropriate fraction
                if (taskToAdd.pTask->m_RangeToRun < rangeToSplit)
                {
                    taskToAdd.partition.end = taskToAdd.partition.start + taskToAdd.pTask->m_RangeToRun;
                    subTask.partition.start = taskToAdd.partition.end;
                }
                taskToAdd.pTask->ExecuteRange(taskToAdd.partition, threadNum);

                --numAdded;
            }
        }

        // Increment completion count by number added plus runningCountOffset to account for start value
        subTask.pTask->m_RunningCount.fetch_add(numAdded + runningCountOffset, std::memory_order_relaxed);

        WakeThreads();
    }

    static bool TryRunTask(U32 threadNum, U32& hintPipeToCheck_io)
    {
        SubTask subTask;
        bool bHaveTask = Pipes::WriterTryReadFront(&subTask, threadNum);

        U32 threadToCheck = hintPipeToCheck_io;
        U32 checkCount = 0;
        while (!bHaveTask && checkCount < s_NumThreads)
        {
            threadToCheck = (hintPipeToCheck_io + checkCount) % s_NumThreads;
            if (threadToCheck != threadNum)
            {
                bHaveTask = Pipes::ReaderTryReadBack(&subTask, threadToCheck);
            }
            ++checkCount;
        }

        if (bHaveTask)
        {
            hintPipeToCheck_io = threadToCheck;

            U32 partitionSize = subTask.partition.end - subTask.partition.start;
            if (subTask.pTask->m_RangeToRun < partitionSize)
            {
                SubTask taskToRun = SplitTask(subTask, subTask.pTask->m_RangeToRun);
                SplitAndAddTask(gtl_threadNum, subTask, subTask.pTask->m_RangeToRun, 0);
                taskToRun.pTask->ExecuteRange(taskToRun.partition, threadNum);
                taskToRun.pTask->m_RunningCount.fetch_sub(1, std::memory_order_relaxed);
            }
            else
            {
                // The task has already been divided up by AddTaskSetToPipe, so just run it
                subTask.pTask->ExecuteRange(subTask.partition, threadNum);
                subTask.pTask->m_RunningCount.fetch_sub(1, std::memory_order_relaxed);
            }
        }

        return bHaveTask;
    }

    static void TaskingThreadFunction(const ThreadArgs& args)
    {
        U32 threadNum = args.threadNum;
        gtl_threadNum = threadNum;

        U32 spinCount = 0;
        U32 hintPipeToCheck_io = threadNum + 1;
        while (s_bRunning.load(std::memory_order_relaxed))
        {
            if (!TryRunTask(threadNum, hintPipeToCheck_io))
            {
                // No task, will spin then wait
                ++spinCount;
                if (spinCount > SPIN_COUNT)
                {
                    bool bHaveTask = false;
                    for (U32 thread = 0; thread < s_NumThreads; ++thread)
                    {
                        if (!Pipes::IsPipeEmpty(thread))
                        {
                            bHaveTask = true;
                            break;
                        }
                    }

                    if (bHaveTask)
                    {
                        // Keep trying
                        spinCount = 0;
                    }
                    else
                    {
                        s_NumThreadsWaiting.fetch_add(1, std::memory_order_relaxed);
                        std::unique_lock<std::mutex> lk(s_NewTaskEventMutex);
                        s_NewTaskEvent.wait(lk);
                        s_NumThreadsWaiting.fetch_sub(1, std::memory_order_relaxed);
                        spinCount = 0;
                    }
                }
                else
                {
                    U32 spinBackoffCount = spinCount * SPIN_BACKOFF_MULTIPLIER;
                    while (spinBackoffCount)
                    {
                        Pause();
                        --spinBackoffCount;
                    }
                }
            }
        }

        s_NumThreadsRunning.fetch_sub(1, std::memory_order_relaxed);

        return;
    }

    static void StartThreads()
    {
        if (s_bHaveThreads)
            return;

        s_bRunning = 1;

        // We create one less thread than s_NumThreads as the main thread counts as one
        s_pThreadNumStore               = new ThreadArgs[s_NumThreads];
        s_pThreads                      = new std::thread*[s_NumThreads];
        s_pThreadNumStore[0].threadNum  = 0;
        s_NumThreadsRunning             = 1; // Account for main thread
        for (U32 thread = 1; thread < s_NumThreads; ++thread)
        {
            s_pThreadNumStore[thread].threadNum = thread;
            s_pThreads[thread] = new std::thread(TaskingThreadFunction, s_pThreadNumStore[thread]);
            ++s_NumThreadsRunning;
        }

        // Ensure we have sufficient tasks to equally fill either all threads including main
        // or just the threads we've launched, this is outside the firstinit as we want to be able
        // to runtime change it
        if (1 == s_NumThreads)
        {
            s_NumPartitions         = 1;
            s_NumInitialPartitions  = 1;
        }
        else
        {
            s_NumPartitions         = s_NumThreads * (s_NumThreads - 1);
            s_NumInitialPartitions  = s_NumThreads - 1;
            if (s_NumInitialPartitions > MAX_NUM_INITIAL_PARTITIONS)
            {
                s_NumInitialPartitions = MAX_NUM_INITIAL_PARTITIONS;
            }
        }

        s_bHaveThreads = true;
    }

    static void StopThreads(bool bWait)
    {
        if (s_bHaveThreads)
        {
            s_bRunning = 0;
            while (bWait && s_NumThreadsRunning > 1)
            {
                // Keep firing event to ensure all threads pick up state of s_bRunning
                s_NewTaskEvent.notify_all();
            }

            for (U32 thread = 1; thread < s_NumThreads; ++thread)
            {
                s_pThreads[thread]->detach();
                delete s_pThreads[thread];
            }

            s_NumThreads = 0;
            delete[] s_pThreadNumStore;
            delete[] s_pThreads;
            s_pThreadNumStore = nullptr;
            s_pThreads = nullptr;

            s_bHaveThreads = false;
            s_NumThreadsWaiting = 0;
            s_NumThreadsRunning = 0;
        }
    }

    bool Init()
    {
        U32 nbThreads = std::thread::hardware_concurrency();

        PARALLAX_TRACE("Initializing threads manager with %d threads...", nbThreads);

        s_NumThreads = nbThreads;
        Pipes::Init(s_NumThreads);

        StartThreads();

        PARALLAX_TRACE("Threads manager initialized");

        return true;
    }

    void Shutdown()
    {
        StopThreads(true);

        PARALLAX_TRACE("Threads engine stopped !");
    }

    void AddTaskToPipe(ITask* pTask)
    {
        // Set completion to -1 to guarantee it won't be found complete until all subtasks added
        pTask->m_RunningCount.store(-1, std::memory_order_relaxed);

        // Divide task up and add to pipe
        pTask->m_RangeToRun = pTask->m_SetSize / s_NumPartitions;
        if (pTask->m_RangeToRun < pTask->m_grainSize)
        {
            pTask->m_RangeToRun = pTask->m_grainSize;
        }

        U32 rangeToSplit = pTask->m_SetSize / s_NumInitialPartitions;
        if (rangeToSplit < pTask->m_grainSize)
            rangeToSplit = pTask->m_grainSize;

        SubTask subTask;
        subTask.pTask = pTask;
        subTask.partition.start = 0;
        subTask.partition.end = pTask->m_SetSize;
        SplitAndAddTask(gtl_threadNum, subTask, rangeToSplit, 1);
    }

    void WaitForTask(const ITask* pTask)
    {
        U32 hintPipeToCheck_io = gtl_threadNum + 1;
        if (pTask)
        {
            while (!pTask->GetIsComplete())
            {
                TryRunTask(gtl_threadNum, hintPipeToCheck_io);
                // Should add a spin then wait for task completion event.
            }
        }
        else
        {
            TryRunTask(gtl_threadNum, hintPipeToCheck_io);
        }
    }

    void WaitForAll()
    {
        bool bHaveTask = true;
        U32 hintPipeToCheck_io = gtl_threadNum + 1;
        I32 numThreadsRunning = s_NumThreadsRunning.load(std::memory_order_relaxed) - 1;

        while (bHaveTask || s_NumThreadsWaiting.load(std::memory_order_relaxed) < numThreadsRunning)
        {
            TryRunTask(gtl_threadNum, hintPipeToCheck_io);
            bHaveTask = false;
            for (U32 thread = 0; thread < s_NumThreads; ++thread)
            {
                if (!Pipes::IsPipeEmpty(thread))
                {
                    bHaveTask = true;
                    break;
                }
            }
        }
    }

    void WaitForAllAndShutdown()
    {
        WaitForAll();
        Shutdown();
    }

    U32 GetNumTaskThreads()
    {
        return s_NumThreads;
    }
}
