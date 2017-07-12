#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include <Parallax/Threads/Worker.hpp>
#include <Parallax/Types.hpp>

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
    /**
     * \namespace   Parallax::Threads
     * \ingroup     PIL
     */
    namespace Threads
    {
        /**
         * \class   ThreadManager
         * \ingroup PIL
         *
         * \brief
         *  The ThreadManager handle all the workers and distribute tasks among them
         */
        class ThreadManager
        {
        public:
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   nbThread    Number of threads to use at the start
             */
            ThreadManager (U32 nbThread = std::thread::hardware_concurrency());
            /**
             * \brief
             *  Destructor
             */
            ~ThreadManager();

            /**
             * \brief
             *  Stop the ThreadManager. The ThreadManager will stop all workers !
             *
             * \return  An pair representing the success of the function paired with an error message if necessary
             */
            std::pair<bool, std::string> stop();
            /**
             * \brief
             *  Get an available worker from the ThreadManager
             *
             * \return  An availablable worker
             */
            std::shared_ptr<Worker> getWorker();
            /**
             * \brief
             *  Start a task on a specified worker
             *
             * \param[in]   worker  The worker where we want to execute the task
             * \param[in]   task    The task to execute
             */
            void startTask(std::shared_ptr<Worker> worker, const Task& task);

        private:
            /**
             * \brief
             *  Round to next power a given number
             *
             * \param[in]   nbThread    The number to round to next power
             *
             * \return  The result of the computation
             */
            U32 roundToNextPower(U32 nbThread) const;
            /**
             * \brief
             *  Add a worker to work with
             */
            void addNewThread();

        private:
            std::vector<std::shared_ptr<Worker>>    m_workers;          /*!<    Stock of workers                    */
            std::mutex                              m_workersMutex;     /*!<    Mutex for using stock of workers    */

            mutable std::condition_variable         m_cv;               /*!<    Condition variable for workers      */
            mutable std::mutex                      m_condvarMutex;     /*!<    Mutex for condition variable        */

            std::atomic_bool                        m_running;          /*!<    Is the ThreadManager running ?      */
        };
    }
}

#endif
