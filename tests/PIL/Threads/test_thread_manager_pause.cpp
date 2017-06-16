#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Threads/ThreadPool.hpp>

#include <tests.hpp>
#include <iostream>
#include <unistd.h>
#include <atomic>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Threads::ThreadManager manager(1);
    Threads::ThreadPool pool(2, manager);

    pool.start();

    Threads::Task t;
    Threads::Task t2;

    t.assign([]() {
        sleep(3);
    });

    t2.assign([]() {
        sleep(2);
    });

    pool.addTask(t2);

    pool.pause();
    pool.unpause();

    t.setPauseFunction([]() {
        register_test(true, "Task successfully pause when we pause the pool");
    });
    t.setUnPauseFunction([]() {
        register_test(true, "Task successfully unpause when we pause the pool");
    });

    pool.addTask(t);

    pool.pause();

    sleep(1);

    pool.unpause();

    pool.stop();

    return end_test();
}
