#ifndef PARALLAX_WORKER_HPP_GUARD
#define PARALLAX_WORKER_HPP_GUARD

#include <Parallax/Threads/Task.hpp>

namespace Parallax
{
    /**
     * \namespace   Parallax::Threads
     * \ingroup     PIL
     */
    namespace Threads
    {
        /**
         * \enum    state
         * \ingroup PIL
         *
         * \brief
         *  Working states
         */
        enum class state {
            STOP = 0,           /*!<    STOPPED     */
            PAUSE,              /*!<    PAUSED      */
            START               /*!<    STARTED     */
        };

        /**
         * \class   Worker
         * \ingroup PIL
         *
         * \brief
         *  Represent a worker that execute tasks
         */
        class Worker
        {
        public:
            /**
             * \brief
             *  Constructor
             */
            Worker();
            /**
             * \brief
             *  Destructor
             */
            ~Worker();

            /**
             * \brief
             *  Start this worker
             *
             * \param[in]   cv              Variable condition for this worker
             * \param[in]   condvarMutex    Mutex to handle the variable condition
             *
             * \throw   std::runtime_error
             */
            void start(std::condition_variable& cv, std::mutex& condvarMutex);

            /**
             * \brief
             *  Start a task
             *
             * \param[in]   task    The task to execute on this worker
             *
             * \throw   std::runtime_error
             */
            void start(const Task& task);
            /**
             * \brief
             *  Stop this worker
             */
            void stop();
            /**
             * \brief
             *  Stop the task on this worker
             */
            void stopTask();
            /**
             * \brief
             *  Pause the task on this worker
             */
            void pauseTask();
            /**
             * \brief
             *  Unpause the task on this worker
             */
            void unpauseTask();
            /**
             * \brief
             *  Wait the task to be stopped
             */
            void waitStopped();
            /**
             * \brief
             *  Set a new task described by its function to execute
             *
             * \param[in]   task    The function the task has to execute
             */
            void setTask(const std::function<void()>& task);
            /**
             * \brief
             *  Set a new task on this worker
             *
             * \param[in]   task    The task to execute on this worker
             */
            void setTask(const Task& task);
            /**
             * \brief
             *  Whether or not this worker is idling
             *
             * \return  True if the worker is idle, false otherwise
             */
            bool isIdle();
            /**
             * \brief
             *  Indicate if this worker is reserved or not
             *
             * \param[in]   status  The new status of this worker
             */
            void setReserved(bool status);
            /**
             * \brief
             *  Know whether or not this worker is reserved
             *
             * \return  True if the worker is reserved, false otherwise
             */
            bool isReserved();

        private:
            /**
             * \brief
             *  The thread function
             *
             * \param[in]   cv              The thread variable condition
             * \param[in]   condvarMutex    The thread mutex to handle the variable condition
             */
            void threadMain(std::condition_variable& cv, std::mutex& condvarMutex);

        private:
            Task                m_task;         /*!<    The task to execute                 */
            std::thread         m_thread;       /*!<    The worker thread                   */
            std::mutex          m_taskMutex;    /*!<    The mutex to handle the task        */
            std::atomic_bool    m_running;      /*!<    The running status of the worker    */
            std::atomic_bool    m_reserved;     /*!<    The reserved status of the worker   */
        };
    }
}

#endif
