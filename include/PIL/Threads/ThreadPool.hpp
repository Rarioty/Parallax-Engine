#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Types.hpp>

#include <future>
#include <queue>

namespace Parallax
{
    namespace Threads
    {
        class ThreadPool
        {
        public:
            ThreadPool(unsigned int nbThreads, ThreadManager& manager);
            virtual ~ThreadPool();

            std::pair<bool, std::string>    start();
            std::pair<bool, std::string>    pause();
            std::pair<bool, std::string>    unpause();
            std::pair<bool, std::string>    stop();
            void resize(unsigned int maxParallelism);

            void addTask(Task& task);

            template <class F, class... Args>
            auto addTask(F&& function, Args&&... args)
                -> std::future<typename std::result_of<F(Args...)>::type>;

        private:
            void startTask();
            void decreaseRefCount();
            void removeWorkerRef(std::shared_ptr<Worker> worker);

        private:
            std::queue<Task>                        m_taskContainer;
            std::mutex                              m_taskMutex;

            U32                                     m_threadRefCount;
            std::mutex                              m_refCountMutex;

            ThreadManager&                          m_manager;

            std::atomic<state>                      m_status;
            U32                                     m_maxParallelism;

            std::vector<std::shared_ptr<Worker>>    m_workers;
            std::mutex                              m_workerMutex;
        };

        #include "ThreadPool.inc"
    }
}

#endif
