#include <Parallax/Threads/ITask.hpp>

namespace Parallax::Threads
{
    ITask::ITask()
        : m_SetSize(1)
        , m_grainSize(1)
        , m_RangeToRun(1)
        , m_RunningCount(0)
    {}

    ITask::ITask(U32 setSize)
        : m_SetSize(setSize)
        , m_grainSize(1)
        , m_RangeToRun(1)
        , m_RunningCount(0)
    {}

    ITask::ITask(U32 setSize, U32 grainSize)
        : m_SetSize(setSize)
        , m_grainSize(grainSize)
        , m_RangeToRun(1)
        , m_RunningCount(0)
    {}

    bool ITask::GetIsComplete() const
    {
        return 0 == m_RunningCount.load(std::memory_order_relaxed);
    }

    Task::Task(TaskFunction func)
        : m_Function(func)
    {}

    Task::Task(U32 setSize, TaskFunction func)
        : ITask(setSize)
        , m_Function(func)
    {}

    void Task::ExecuteRange(TaskPartition range, U32 threadNum)
    {
        m_Function(range, threadNum);
    }
}
