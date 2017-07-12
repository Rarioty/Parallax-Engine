#include <Parallax/Threads/ThreadManager.hpp>
#include <Parallax/Threads/ThreadPool.hpp>

#include <tests.hpp>
#include <iostream>
#include <unistd.h>
#include <atomic>

std::atomic_bool    run(true);
int asked_to_stop = 0;

using namespace Parallax;

int main(int argc, char* argv[])
{
    Threads::ThreadManager manager(1);
    Threads::ThreadPool pool(2, manager);

    pool.start();

    Threads::Task t;

    t = ([]() {
        int i = 1;
        while (run.load())
        {
            std::cerr << i++ << ".";
            sleep(1);
        }
    });

    t.setStopFunction([](){
        run.store(false);
        std::cerr << std::endl;
        register_test(true, "Task successfully stop when we ask it to stop");
        asked_to_stop++;
    });
    t.getStopFunction();        // For coverage test

    pool.addTask(t);

    std::cerr << "In 3 seconds the task will stop...";
    sleep(2);
    t.stop();

    pool.stop();

    register_test(asked_to_stop == 2, "The pool stop so we called two times the task to stop");

    return end_test();
}
