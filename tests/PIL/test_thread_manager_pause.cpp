#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Threads/ThreadPool.hpp>

#include <tests.hpp>
#include <iostream>
#include <unistd.h>
#include <atomic>

using namespace Parallax;

std::atomic_bool    paused(false);

int main(int argc, char* argv[])
{
    int ret = 0;

    Threads::ThreadManager manager(1);
    Threads::ThreadPool pool(2, manager);

    pool.start();

    Threads::Task t;

    t.assign([]() {
        int i = 0;
        std::cout << "Starting task" << std::endl;
        while (i <= 5)
        {
            std::cout << "Current: " << i << std::endl;
            sleep(1);

            if (not paused.load())
                i++;
        }
    });

    t.setPauseFunction([]() {
        std::cout << "Pause" << std::endl;
        paused.store(true);
    });
    t.setUnPauseFunction([]() {
        std::cout << "Unpause" << std::endl;
        paused.store(false);
    });

    pool.addTask(t);

    sleep(2);

    pool.pause();

    sleep(2);

    pool.unpause();

    pool.stop();

    return ret;
}
