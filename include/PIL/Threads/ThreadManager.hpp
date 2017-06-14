#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include <PIL/Threads/Worker.hpp>
#include <PIL/Types.hpp>

#include <atomic>
#include <thread>
#include <atomic>
#include <memory>
#include <condition_variable>
#include <vector>
#include <utility>
#include <string>
#include <iostream>

namespace Parallax
{
    namespace Threads
    {
        class ThreadManager
        {
        public:
            ThreadManager (U32 nbThread = std::thread::hardware_concurrency());
            ~ThreadManager();

            std::pair<bool, std::string> stop();
            std::shared_ptr<Worker> getWorker();
            void startTask(std::shared_ptr<Worker> worker, const Task& task);

        private:
            U32 roundToNextPower(U32 nbThread) const;
            void addNewThread();

        private:
            std::vector<std::shared_ptr<Worker>>    m_workers;
            std::mutex                              m_workersMutex;

            mutable std::condition_variable         m_cv;
            mutable std::mutex                      m_condvarMutex;

            std::atomic_bool                        m_running;
        };
    }
}

#endif
