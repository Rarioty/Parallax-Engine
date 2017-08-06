#ifndef PARALLAX_ITASK_HPP_GUARD
#define PARALLAX_ITASK_HPP_GUARD

#include <Parallax/Types.hpp>
#include <functional>
#include <atomic>

namespace Parallax
{
    namespace Threads
    {
        struct TaskPartition
        {
            uint32_t start;
            uint32_t end;
        };

        class ITask
        {
        public:
            ITask();
            ITask(U32 setSize);
            ITask(U32 setSize, U32 grainSize);

            virtual void ExecuteRange(TaskPartition range, U32 threadNum) = 0;

            bool GetIsComplete() const;

        public:
            U32                 m_SetSize;
            U32                 m_grainSize;
            U32                 m_RangeToRun;
            std::atomic<I32>    m_RunningCount;
        };

        typedef std::function<void (TaskPartition range, U32 threadNum)> TaskFunction;
        class Task : public ITask
        {
        public:
            Task() = default;
            Task(TaskFunction func);
            Task(U32 setSize, TaskFunction func);

            virtual void ExecuteRange(TaskPartition range, U32 threadNum) override;

        public:
            TaskFunction    m_Function;
        };

        struct SubTask
        {
            ITask*          pTask;
            TaskPartition   partition;
        };
    }
}

#endif
