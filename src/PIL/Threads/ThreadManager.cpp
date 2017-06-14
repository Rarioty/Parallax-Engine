#include <PIL/Threads/ThreadManager.hpp>

namespace Parallax::Threads
{
    ThreadManager::ThreadManager(U32 nbThread)
        : m_running(true)
    {
        for (U32 i = 0; i < nbThread; ++i)
        {
            this->addNewThread();
        }
    }

    ThreadManager::~ThreadManager()
    {
        if (this->m_running.load())
            this->stop();

        {
            std::lock_guard<std::mutex> guard(this->m_workersMutex);
            m_workers.clear();
        }
    }

    void ThreadManager::addNewThread()
    {
        std::lock_guard<std::mutex> guard(this->m_workersMutex);

        this->m_workers.emplace_back(new Worker);
        this->m_workers.back()->start(this->m_cv, this->m_condvarMutex);
    }

    U32 ThreadManager::roundToNextPower(U32 nbThread) const
    {
        nbThread |= nbThread >>  1;
        nbThread |= nbThread >>  2;
        nbThread |= nbThread >>  4;
        nbThread |= nbThread >>  8;
        nbThread |= nbThread >> 16;
        ++nbThread;

        return nbThread;
    }

    std::shared_ptr<Worker>
    ThreadManager::getWorker()
    {
        U32 maxThreads;
        U32 nbWorkers;

        if (not this->m_running.load())
            return nullptr;

        {
            std::lock_guard<std::mutex> guard(this->m_workersMutex);

            for (auto& worker : this->m_workers)
            {
                if (worker->isIdle() && not worker->isReserved())
                {
                    worker->setReserved(true);
                    return worker;
                }
            }
        }

        {
            std::lock_guard<std::mutex> guard(this->m_workersMutex);

            nbWorkers = this->m_workers.size();
            maxThreads = roundToNextPower(nbWorkers);
        }

        for (unsigned int i = 0; i < maxThreads - nbWorkers; ++i)
        {
            this->addNewThread();
        }

        return this->getWorker();
    }

    void ThreadManager::startTask(std::shared_ptr<Worker> worker, const Task& task)
    {
        worker->setTask(task);
        this->m_cv.notify_all();
    }

    std::pair<bool, std::string>
    ThreadManager::stop()
    {
        std::lock_guard<std::mutex> guard(this->m_workersMutex);

        if (this->m_running.load() == false)
        {
            return std::make_pair(false, "ThreadManager is already stopped");
        }

        this->m_running.store(false);
        for (auto& worker : this->m_workers)
            worker->stop();
        this->m_cv.notify_all();
        return std::make_pair(true, "");
    }
}
