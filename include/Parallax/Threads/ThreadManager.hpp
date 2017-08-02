#ifndef PARALLAX_THREADMANAGER_HPP_GUARD
#define PARALLAX_THREADMANAGER_HPP_GUARD

#include <Parallax/Threads/ITask.hpp>
#include <Parallax/Types.hpp>

namespace Parallax
{
    /**
     * \namespace   Parallax::Threads
     * \ingroup     PIL
     */
    namespace Threads
    {
        namespace Manager
        {
            bool Init();
            void Shutdown();

            void AddTaskToPipe(ITask* pTask);
            void WaitForTask(const ITask* pTask);
            void WaitForAll();
            void WaitForAllAndShutdown();

            U32 GetNumTaskThreads();
        }


    }
}

#endif
