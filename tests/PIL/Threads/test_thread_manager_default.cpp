#include <Parallax/Threads/ThreadManager.hpp>

#include <Parallax/Threads/ITask.hpp>

#include <tests.hpp>
#include <iostream>

using namespace Parallax;

#define VECTOR_LEN  32

int vector[VECTOR_LEN];
int result[VECTOR_LEN];

int main(int argc, char* argv[])
{
    U32 i;

    Threads::Manager::Init();

    std::cout << Threads::Manager::GetNumTaskThreads() << " threads were created !" << std::endl;

    for (i = 0; i < VECTOR_LEN; ++i)
    {
        int tmp = rand() % 1000;
        vector[i] = tmp;
        result[i] = tmp * 2;
    }

    Threads::TaskFunction mulFunc = [](Threads::TaskPartition range, U32 threadNum){
        U32 i;
        for (i = range.start; i < range.end; ++i)
        {
            vector[i] *= 2;
        }
    };
    Threads::Task task(VECTOR_LEN, mulFunc);

    Threads::Manager::AddTaskToPipe(&task);
    Threads::Manager::WaitForTask(&task);

    // Verify result
    for (i = 0; i < VECTOR_LEN; ++i)
    {
        std::cerr << "vector[" << i << "] = " << vector[i] << " ==? " << result[i] << std::endl;
        register_test(vector[i] == result[i], "The two values are the same");
    }

    Threads::Manager::WaitForAllAndShutdown();

    return end_test();
}
