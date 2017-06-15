#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Types.hpp>

#include <future>
#include <queue>

namespace Parallax
{
    /**
     * \namespace   Parallax::Threads
     * \ingroup     PIL
     */
    namespace Threads
    {
        /**
         * \class   ThreadPool
         * \ingroup PIL
         *
         * \brief
         *  The ThreadPool allow to handle multiple tasks above the ThreadManager.
         *  With this class, we can launch tasks without knowing on which worker they
         *  are executed.
         */
        class ThreadPool
        {
        public:
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   nbThreads   Number of threads max to use
             * \param[in]   manager     The ThreadManager to use with this ThreadPool
             *
             * \throw   std::invalid_argument
             */
            ThreadPool(unsigned int nbThreads, ThreadManager& manager);
            /**
             * \brief
             *  Destructor
             */
            virtual ~ThreadPool();

            /**
             * \brief
             *  Start the ThreadPool
             *
             * \return  A value representing the success of this function paired with an error message if necessary
             */
            std::pair<bool, std::string>    start();
            /**
             * \brief
             *  Pause the ThreadPool
             *
             * \return  A value representing the success of this function paired with an error message if necessary
             */
            std::pair<bool, std::string>    pause();
            /**
             * \brief
             *  Unpause the ThreadPool
             *
             * \return  A value representing the success of this function paired with an error message if necessary
             */
            std::pair<bool, std::string>    unpause();
            /**
             * \brief
             *  Stop the ThreadPool
             *
             * \return  A value representing the success of this function paired with an error message if necessary
             */
            std::pair<bool, std::string>    stop();
            /**
             * \brief
             *  Resize the number of threads allowed
             *
             * \param[in]   maxParallelism  The new max number of threads allowed
             */
            void resize(unsigned int maxParallelism);

            /**
             * \brief
             *  Launch a task with the ThreadManager
             *
             * \param[in]   task    The task to launch
             *
             * \throw   std::runtime_error
             */
            void addTask(Task& task);

            /**
             * \brief
             *  Launch a task with the ThreadManager
             *
             * \param[in]   function    The function the task has to execute
             * \param[in]   args        The arguments to pass to the function to execute
             *
             * \throw   std::runtime_error
             *
             * \return  The return value of the function to execute
             */
            template <class F, class... Args>
            auto addTask(F&& function, Args&&... args)
                -> std::future<typename std::result_of<F(Args...)>::type>;

        private:
            /**
             * \brief
             *  Launch a stocked task on the ThreadManager if any worker is available
             */
            void startTask();
            /**
             * \brief
             *  Decrease the current number of threads used
             */
            void decreaseRefCount();
            /**
             * \brief
             *  Remove a worker pointer in the worker stock
             *
             * \param[in]   worker  The worker to remove
             */
            void removeWorkerRef(std::shared_ptr<Worker> worker);

        private:
            std::queue<Task>                        m_taskContainer;    /*!<    The task container                              */
            std::mutex                              m_taskMutex;        /*!<    Mutex for task container management             */

            U32                                     m_threadRefCount;   /*!<    Current number of threads used                  */
            std::mutex                              m_refCountMutex;    /*!<    Mutex to handle the current number of threads   */

            ThreadManager&                          m_manager;          /*!<    ThreadManager used with this pool               */

            std::atomic<state>                      m_status;           /*!<    Status of the ThreadPool                        */
            U32                                     m_maxParallelism;   /*!<    Maximum number of threads allowed               */

            std::vector<std::shared_ptr<Worker>>    m_workers;          /*!<    Stock of used workers                           */
            std::mutex                              m_workerMutex;      /*!<    Mutex to handle the workers used                */
        };

        #include "ThreadPool.inc"
    }
}

#endif
