#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Threads/ThreadPool.hpp>

#include <tests.hpp>
#include <iostream>
#include <unistd.h>
#include <atomic>

std::atomic_bool    run(true);

using namespace Parallax;

int main(int argc, char* argv[])
{
    int ret = 0;

    Threads::ThreadManager manager(1);
    Threads::ThreadPool pool(2, manager);

    pool.start();

    Threads::Task t;

    t = ([]() {
        while (run.load())
        {
            std::cout << "Running" << std::endl;
            sleep(1);
        }
    });

    t.setStopFunction([](){
        run.store(false);
    });
    t.getStopFunction();        // For coverage test

    pool.addTask(t);

    sleep(4);
    t.stop();

    pool.stop();

    return ret;
}
