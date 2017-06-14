#ifndef WORKER_HPP
#define WORKER_HPP

#include <PIL/Threads/Task.hpp>

namespace Parallax
{
    namespace Threads
    {
        enum class state { STOP = 0, PAUSE, START };

        class Worker
        {
        public:
            Worker();
            ~Worker();

            void start(std::condition_variable& cv, std::mutex& condvarMutex);

            void start(const Task& task);
            void stop();
            void stopTask();
            void pauseTask();
            void unpauseTask();
            void waitStopped();
            void setTask(const std::function<void()>& task);
            void setTask(const Task& task);
            bool isIdle();
            void setReserved(bool status);
            bool isReserved();

        private:
            void threadMain(std::condition_variable& cv, std::mutex& condvarMutex);

        private:
            Task                m_task;
            std::thread         m_thread;
            std::mutex          m_taskMutex;
            std::atomic_bool    m_running;
            std::atomic_bool    m_reserved;
        };
    }
}

#endif
