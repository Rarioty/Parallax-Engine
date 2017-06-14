#include <PIL/Threads/ThreadPool.hpp>

#include <algorithm>

namespace Parallax::Threads
{
    ThreadPool::ThreadPool(U32 nbThreads, ThreadManager& manager)
        : m_threadRefCount(0)
        , m_manager(manager)
        , m_status (state::START)
        , m_maxParallelism(nbThreads)
    {
        if (nbThreads == 0)
            throw std::invalid_argument("The ThreadPool must have at least a thread");
    }

    ThreadPool::~ThreadPool()
    {
        if (this->m_status.load(std::memory_order_seq_cst) != state::STOP)
        {
            this->stop();
        }
    }

    std::pair<bool, std::string>
    ThreadPool::start()
    {
        if (this->m_status.load(std::memory_order_seq_cst) != state::STOP)
            return std::make_pair(false, "ThreadPool has already been started");

        m_status.store(state::START, std::memory_order_seq_cst);

        return std::make_pair(true, "");
    }

    std::pair<bool, std::string>
    ThreadPool::pause()
    {
        if (this->m_status.load(std::memory_order_seq_cst) != state::START)
            return std::make_pair(false, "ThreadPool is not started");

        m_status.store(state::PAUSE, std::memory_order_seq_cst);

        std::lock_guard<std::mutex> guardWorker (this->m_workerMutex);
        for (auto& worker : this->m_workers)
        {
            worker->pauseTask();
        }
        return std::make_pair(true, "");
    }

    std::pair<bool, std::string>
    ThreadPool::unpause()
    {
        if (this->m_status.load(std::memory_order_seq_cst) != state::PAUSE)
            return std::make_pair(false, "ThreadPool is not paused");

        m_status.store(state::START, std::memory_order_seq_cst);

        {
            std::lock_guard<std::mutex> guardWorker (this->m_workerMutex);
            for (auto& worker : this->m_workers)
            {
                worker->unpauseTask();
            }
        }
        this->startTask();
        return std::make_pair(true, "");
    }

    std::pair<bool, std::string>
    ThreadPool::stop()
    {
        bool waitCondition;
        if (this->m_status.load(std::memory_order_seq_cst) == state::STOP)
            return std::make_pair(false, "ThreadPool is already stopped");

        m_status.store(state::STOP, std::memory_order_seq_cst);

        {
            std::lock_guard<std::mutex> guardWorker (this->m_workerMutex);
            for (auto& worker : this->m_workers)
            {
                worker->stopTask();
            }
        }

        do {
            {
                std::lock_guard<std::mutex> guardWorker (this->m_workerMutex);
                waitCondition = (not this->m_workers.empty() || not this->m_taskContainer.empty());
            }

            if (waitCondition)
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } while (waitCondition);

        return std::make_pair(true, "");
    }

    void ThreadPool::resize(U32 maxParallelism)
    {
        std::lock_guard<std::mutex> guardRef (this->m_refCountMutex);
        this->m_maxParallelism = maxParallelism;
    }

    void ThreadPool::addTask(Task& task)
    {
        if (this->m_status.load(std::memory_order_release) == state::STOP)
            throw std::runtime_error("Can't add task on stopped ThreadPool");

        {
            std::lock_guard<std::mutex> guard (this->m_taskMutex);
            this->m_taskContainer.push(task);
        }

        this->startTask();
    }

    void ThreadPool::decreaseRefCount()
    {
        std::lock_guard<std::mutex> guardRef (this->m_refCountMutex);
        --(this->m_threadRefCount);
    }

    void ThreadPool::startTask()
    {
        std::lock_guard<std::mutex> guardRef (this->m_refCountMutex);
        std::lock_guard<std::mutex> guardTask (this->m_taskMutex);
        std::lock_guard<std::mutex> guardWorker (this->m_workerMutex);
        std::shared_ptr<Worker> worker;
        Task task;

        if (this->m_taskContainer.empty() || this->m_threadRefCount >= this->m_maxParallelism ||
            this->m_status.load(std::memory_order_release) == state::PAUSE)
            return;

        ++ this->m_threadRefCount;

        worker = this->m_manager.getWorker();
        task = std::move(this->m_taskContainer.front());
        this->m_taskContainer.pop();

        this->m_workers.emplace_back(worker);
        task.addCallback([this, worker] {
            this->removeWorkerRef(worker);
            this->decreaseRefCount();
            this->startTask();
        });

        m_manager.startTask(worker, task);
        if (this->m_status.load(std::memory_order_release) == state::STOP)
            task.stop();
    }

    void ThreadPool::removeWorkerRef(std::shared_ptr<Worker> worker)
    {
        std::lock_guard<std::mutex> guardWorker (this->m_workerMutex);
        this->m_workers.erase(std::remove_if(this->m_workers.begin(),
                                             this->m_workers.end(),
                                             [worker](const auto& w) { return w == worker; }),
                                         this->m_workers.end());
    }
}
