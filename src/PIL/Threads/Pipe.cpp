#include <Parallax/Threads/Pipe.hpp>

#include <Parallax/Debug/Debug.hpp>

#include <cstring>
#include <atomic>
#include <thread>

namespace Parallax::Threads::Pipes
{
    static const U32            PIPESIZE_LOG2   = 8;

    const static U32            ms_cSize        = ( 1 << PIPESIZE_LOG2 );
    const static U32            ms_cIndexMask   = ms_cSize - 1;
    const static U32            FLAG_INVALID    = 0xFFFFFFFF; // 32bit for CAS
    const static U32            FLAG_CAN_WRITE  = 0x00000000; // 32bit for CAS
    const static U32            FLAG_CAN_READ   = 0x11111111; // 32bit for CAS

    typedef SubTask             SubTaskTable[ms_cSize];
    typedef std::atomic<U32>    FlagsTable[ms_cSize];

    static SubTaskTable*        s_Buffer;
    static std::atomic<U32>*    s_WriteIndex;
    static std::atomic<U32>*    s_ReadCount;
    static FlagsTable*          s_Flags;
    static std::atomic<U32>*    s_ReadIndex;

    bool Init(U32 nbPipes)
    {
        U32 i;

        s_Buffer        = new SubTaskTable[nbPipes];
        s_WriteIndex    = new std::atomic<U32>[nbPipes];
        s_ReadCount     = new std::atomic<U32>[nbPipes];
        s_Flags         = new FlagsTable[nbPipes];
        s_ReadIndex     = new std::atomic<U32>[nbPipes];

        for (i = 0; i < nbPipes; ++i)
        {
            s_WriteIndex[i] = 0;
            s_ReadCount[i] = 0;
            s_ReadIndex[i] = 0;

            memset((void*)s_Flags[i], 0, sizeof(s_Flags[i]));
        }

        return true;
    }

    void Shutdown()
    {
        delete[] s_Buffer;
        delete[] s_WriteIndex;
        delete[] s_ReadCount;
        delete[] s_Flags;
        delete[] s_ReadIndex;

        PARALLAX_TRACE("Threads pipe shutdowned");
    }

    bool ReaderTryReadBack(SubTask* pOut, U32 pipeNumber)
    {
        U32 actualReadIndex;
        U32 readCount = s_ReadCount[pipeNumber].load(std::memory_order_relaxed);

        U32 readIndexToUse = readCount;
        while (true)
        {
            U32 writeIndex = s_WriteIndex[pipeNumber].load(std::memory_order_relaxed);
            U32 numInPipe = writeIndex - readCount;

            if (0 == numInPipe)
            {
                return false;
            }
            if (readIndexToUse >= writeIndex)
            {
                readIndexToUse = s_ReadIndex[pipeNumber].load(std::memory_order_relaxed);
            }

            actualReadIndex = readIndexToUse & ms_cIndexMask;

            U32 previous = FLAG_CAN_READ;
            s_Flags[pipeNumber][actualReadIndex].compare_exchange_weak(previous, FLAG_INVALID, std::memory_order_relaxed);
            if (FLAG_CAN_READ == previous)
            {
                break;
            }
            ++readIndexToUse;

            readCount = s_ReadCount[pipeNumber].load(std::memory_order_relaxed);
        }

        s_ReadCount[pipeNumber].fetch_add(1, std::memory_order_relaxed);

        std::atomic_thread_fence(std::memory_order_relaxed);

        *pOut = s_Buffer[pipeNumber][actualReadIndex];

        s_Flags[pipeNumber][actualReadIndex].store(FLAG_CAN_WRITE, std::memory_order_relaxed);

        return true;
    }

    bool WriterTryReadFront(SubTask* pOut, U32 pipeNumber)
    {
        U32 writeIndex = s_WriteIndex[pipeNumber].load(std::memory_order_relaxed);
        U32 frontReadIndex = writeIndex;

        U32 actualReadIndex = 0;
        while (true)
        {
            U32 readCount = s_ReadCount[pipeNumber].load(std::memory_order_relaxed);

            U32 numInPipe = writeIndex - readCount;
            if (0 == numInPipe)
            {
                s_ReadIndex[pipeNumber].store(readCount, std::memory_order_relaxed);
                return false;
            }
            --frontReadIndex;
            actualReadIndex = frontReadIndex & ms_cIndexMask;
            U32 previous = FLAG_CAN_READ;
            bool success = s_Flags[pipeNumber][actualReadIndex].compare_exchange_weak(previous, FLAG_INVALID, std::memory_order_relaxed);
            if (success)
            {
                break;
            }
            else if (s_ReadIndex[pipeNumber].load(std::memory_order_acquire) >= frontReadIndex)
            {
                return false;
            }
        }

        std::atomic_thread_fence(std::memory_order_acquire);
        *pOut = s_Buffer[pipeNumber][actualReadIndex];

        s_Flags[pipeNumber][actualReadIndex].store(FLAG_CAN_WRITE, std::memory_order_relaxed);

        s_WriteIndex[pipeNumber].store(writeIndex-1, std::memory_order_relaxed);

        return true;
    }

    bool WriterTryWriteFront(const SubTask& in, U32 pipeNumber)
    {
        U32 writeIndex = s_WriteIndex[pipeNumber];

        U32 actualWriteIndex = writeIndex & ms_cIndexMask;

        if (s_Flags[pipeNumber][actualWriteIndex].load(std::memory_order_relaxed) != FLAG_CAN_WRITE)
        {
            return false;
        }

        s_Buffer[pipeNumber][actualWriteIndex] = in;
        s_Flags[pipeNumber][actualWriteIndex].store(FLAG_CAN_READ, std::memory_order_relaxed);

        std::atomic_thread_fence(std::memory_order_release);

        s_WriteIndex[pipeNumber].fetch_add(1, std::memory_order_relaxed);

        return true;
    }

    bool IsPipeEmpty(U32 pipeNumber)
    {
        return 0 == s_WriteIndex[pipeNumber].load(std::memory_order_relaxed) - s_ReadCount[pipeNumber].load(std::memory_order_relaxed);
    }

    void Clear(U32 pipeNumber)
    {
        s_WriteIndex[pipeNumber] = 0;
        s_ReadIndex[pipeNumber] = 0;
        s_ReadCount[pipeNumber] = 0;
        memset((void*)s_Flags, 0, sizeof(s_Flags));
    }
}
