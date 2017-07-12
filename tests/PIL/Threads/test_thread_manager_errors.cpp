#include <Parallax/Threads/ThreadManager.hpp>
#include <Parallax/Threads/ThreadPool.hpp>

#include <tests.hpp>
#include <unistd.h>

using namespace Parallax;

int main(int argc, char* argv[])
{
    // Initializing variables
    std::pair<bool, std::string> result;
    Threads::ThreadManager manager(1);
    Threads::ThreadPool* pool;
    int ret;

    // First test: try to initialize with 0 threads
    ret = 0;
    try {
        pool = new Threads::ThreadPool(0, manager);
    } catch(std::invalid_argument ex) {
        ret = 1;
    }
    register_test(ret == 1, "Creation of ThreadPool with zero threads returned an exception");

    pool = new Threads::ThreadPool(2, manager);
    Threads::Task t;

    t = ([](){
        sleep(1);
    });

    // Second test: Try to add a task when the pool is stopped
    pool->stop();
    ret = 0;
    try {
        pool->addTask(t);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Adding a task with the pool stopped returned an exception");

    ret = 0;
    try {
        pool->addTask([](){
            1+1;
        });
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Adding a function task with the pool stopped returned an exception");

    pool->start();
    pool->addTask(Threads::Task([](){
        sleep(1);
    }));
    pool->addTask(Threads::Task([](){
        sleep(1);
    }));
    pool->addTask(Threads::Task([](){
        sleep(1);
    }));
    pool->addTask(Threads::Task([](){
        sleep(1);
    }));
    pool->stop();
    pool->start();

    delete pool;

    pool = new Threads::ThreadPool(2, manager);
    pool->stop();
    result = pool->start();

    register_test(result.first, "Pool successfully started");

    pool->stop();
    result = pool->pause();

    register_test(not result.first, "Pool successfully can't paused when stopped");

    pool->start();
    result = pool->unpause();

    register_test(not result.first, "Pool successfully can't unpause when started");

    pool->stop();
    result = pool->stop();

    register_test(!result.first, "Pool successfully can't stop when already stopped");

    pool->resize(4);

    pool->start();
    pool->addTask([](){
        sleep(1);
    });
    pool->addTask([](){
        sleep(1);
    });

    pool->stop();

    manager.stop();
    manager.getWorker();

    result = manager.stop();

    register_test(!result.first, "Manager successfully can't stop when already stopped");

    return end_test();
}
