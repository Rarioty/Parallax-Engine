#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <future>
#include <mutex>
#include <atomic>
#include <vector>

namespace Parallax
{
    namespace Threads
    {
        /**
         * \class   Task
         *
         * \brief   This class represent a parallel task
         */
        class Task
        {
        public:
            Task();
            explicit Task(const std::function<void()>& func);
            Task(const Task& task);

            virtual ~Task() = default;

            Task& operator=(const Task& other);
            Task& operator=(const std::function<void()> function);

            void operator()();

            template <typename T>
            bool operator==(const T& var);

            template <typename T>
            bool operator!=(const T& var);

            template <class F, class... Args>
            auto assign(F&& function, Args&&... args)
            -> std::future<typename std::result_of<F(Args...)>::type>;

            template <class F, class... Args>
            void addCallback(F&& function, Args&&... args);

            template <class F, class... Args>
            void setStopFunction(F&& function, Args&&... args);

            template <class F, class... Args>
            void setPauseFunction(F&& function, Args&&... args);

            template <class F, class... Args>
            void setUnPauseFunction(F&& function, Args&&... args);

            const std::function<void()>&
            getStopFunction();

            void stop() const;
            void pause();
            void unpause();

        private:
            std::function<void()> m_function;
            std::function<void()> m_stopFunction;
            std::function<void()> m_pauseFunction;
            std::function<void()> m_unpauseFunction;

            std::vector<std::function<void()>> m_callbacks;
            std::mutex m_callbackMutex;
        };

        #include "Task.inc"
    }
}

#endif
