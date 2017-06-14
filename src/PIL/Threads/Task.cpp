#include <PIL/Threads/Task.hpp>

namespace Parallax::Threads
{
    Task::Task()
        : m_function(nullptr)
        , m_stopFunction(nullptr)
        , m_pauseFunction(nullptr)
        , m_unpauseFunction(nullptr)
    {}

    Task::Task(const std::function<void()>& func)
        : m_function(func)
    {}

    Task::Task(const Task& task)
        : m_function(task.m_function)
        , m_stopFunction(task.m_stopFunction)
        , m_pauseFunction(task.m_pauseFunction)
        , m_unpauseFunction(task.m_unpauseFunction)
        , m_callbacks(task.m_callbacks)
    {}

    Task& Task::operator=(const Task& other)
    {
        this->m_function = other.m_function;
        this->m_stopFunction = other.m_stopFunction;
        this->m_pauseFunction = other.m_pauseFunction;
        this->m_unpauseFunction = other.m_unpauseFunction;
        this->m_callbacks = other.m_callbacks;

        return *this;
    }

    Task& Task::operator=(const std::function<void()> function)
    {
        this->m_function = function;

        return *this;
    }

    void Task::operator()()
    {
        this->m_function();
        std::lock_guard<std::mutex> lock_guard(m_callbackMutex);
        for (auto callback : this->m_callbacks) { callback(); }
    }

    const std::function<void()>&
    Task::getStopFunction()
    {
        return this->m_stopFunction;
    }

    void Task::stop() const
    {
        if (m_stopFunction)
            m_stopFunction();
    }

    void Task::pause()
    {
        if (m_pauseFunction)
            m_pauseFunction();
    }

    void Task::unpause()
    {
        if (m_unpauseFunction)
            m_unpauseFunction();
    }
}
