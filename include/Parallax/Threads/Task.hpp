#ifndef TASK_HPP
#define TASK_HPP

#include <functional>
#include <future>
#include <mutex>
#include <atomic>
#include <vector>


namespace Parallax
{
    /**
     * \namespace   Parallax::Threads
     * \ingroup     PIL
     */
    namespace Threads
    {
        /**
         * \class   Task
         * \ingroup PIL
         *
         * \brief
         *  A task allow to execute task in parallel in the ThreadPool
         */
        class Task
        {
        public:
            /**
             * \brief   Constructor
             */
            Task();
            /**
             * \brief   Constructor
             *
             * \param[in]   func    Function the task has to execute
             */
            explicit Task(const std::function<void()>& func);
            /**
             * \brief   Copy-Constructor
             *
             * \param[in]   task    The task to copy
             */
            Task(const Task& task);
            /**
             * \brief   Move-Constructor
             *
             * \param[in]   other   The task to move
             */
            Task(Task&& other);

            /**
             * \brief   Destructor
             */
            virtual ~Task() = default;

            /**
             * \brief
             *  Copy the functions of an existing task to this one
             *
             * \param[in]   other   Task to assign here
             *
             * \return  The modified task
             */
            Task& operator=(const Task& other);
            /**
             * \brief
             *  Move the function from an existing one
             *
             * \param[in]   other   Task to move
             *
             * \return The moved task
             */
            Task& operator=(Task&& other);
            /**
             * \brief
             *  Assign a function to this task
             *
             * \param[in]   function    Function to assign to this task
             *
             * \return  The modified task
             */
            Task& operator=(const std::function<void()> function);

            /**
             * \brief
             *  This operator allow to execute the task
             */
            void operator()();

            /**
             * \brief
             *  Compare the task function to another
             *
             * \param[in]   var     Variable to compare to
             *
             * \return  Whether the task function is equals or not
             */
            template <typename T>
            bool operator==(const T& var);

            /**
             * \brief
             *  Compare the task function to another
             *
             * \param[in]   var     Variable to compare to
             *
             * \return  Whether the task function is equals or not
             */
            template <typename T>
            bool operator!=(const T& var);

            /**
             * \brief
             *  Assign a function with arguments to this task
             *
             * \param[in]   function    Function to execute
             * \param[in]   args        Arguments to pass to the function to execute
             *
             * \return  The value returned by the function to execute
             */
            template <class F, class... Args>
            auto assign(F&& function, Args&&... args)
            -> std::future<typename std::result_of<F(Args...)>::type>;

            /**
             * \brief
             *  Add a callback to this task
             *
             * \param[in]   function    Function to execute
             * \param[in]   args        Arguments to pass to the function to execute
             */
            template <class F, class... Args>
            void addCallback(F&& function, Args&&... args);

            /**
             * \brief
             *  Set the function to execute when the task stop
             *
             * \param[in]   function    Function to execute
             * \param[in]   args        Arguments to pass to the function execute
             */
            template <class F, class... Args>
            void setStopFunction(F&& function, Args&&... args);

            /**
             * \brief
             *  Set the function to execute when the task pause
             *
             * \param[in]   function    Function to execute
             * \param[in]   args        Arguments to pass to the function execute
             */
            template <class F, class... Args>
            void setPauseFunction(F&& function, Args&&... args);

            /**
             * \brief
             *  Set the function to execute when the task unpause
             *
             * \param[in]   function    Function to execute
             * \param[in]   args        Arguments to pass to the function execute
             */
            template <class F, class... Args>
            void setUnPauseFunction(F&& function, Args&&... args);

            /**
             * \brief
             *  Getter of the stop function
             *
             * \return  The current stop function of this task
             */
            const std::function<void()>&
            getStopFunction();

            /**
             * \brief
             *  Stop this task
             */
            void stop() const;
            /**
             * \brief
             *  Pause this function
             */
            void pause();
            /**
             * \brief
             *  Unpause this function
             */
            void unpause();

        private:
            std::function<void()> m_function;                   /*!<    Function the task has to execute                                */
            std::function<void()> m_stopFunction;               /*!<    Function to execute when the task stop                          */
            std::function<void()> m_pauseFunction;              /*!<    Function to execute when the task pause                         */
            std::function<void()> m_unpauseFunction;            /*!<    Function to execute when the task unpause                       */

            std::vector<std::function<void()>> m_callbacks;     /*!<    List of callback function to execute when the task finished     */
            std::mutex m_callbackMutex;                         /*!<    Mutex for the callbacks of this task                            */
        };

        #include "Task.inc"
    }
}

#endif
