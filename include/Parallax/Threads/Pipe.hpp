#ifndef PARALLAX_LOCK_LESS_MULTI_READ_PIPE_HPP_GUARD
#define PARALLAX_LOCK_LESS_MULTI_READ_PIPE_HPP_GUARD

#include <Parallax/Threads/ITask.hpp>
#include <Parallax/Types.hpp>

namespace Parallax
{
    namespace Threads
    {
        namespace Pipes
        {
            bool Init(U32 nbPipes);
            void Shutdown();

            bool ReaderTryReadBack(SubTask* pOut, U32 pipeNumber);
            bool WriterTryReadFront(SubTask* pOut, U32 pipeNumber);
            bool WriterTryWriteFront(const SubTask& in, U32 pipeNumber);

            bool IsPipeEmpty(U32 pipeNumber);

            void Clear(U32 pipeNumber);
        }
    }
}

#endif
