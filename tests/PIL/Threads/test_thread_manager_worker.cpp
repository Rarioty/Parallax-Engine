#include <Parallax/Threads/ThreadManager.hpp>
#include <Parallax/Threads/ThreadPool.hpp>
#include <Parallax/Threads/Worker.hpp>

#include <tests.hpp>
#include <unistd.h>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Threads::ThreadManager* manager = new Threads::ThreadManager(1);
    Threads::ThreadPool pool(2, *manager);

    pool.start();

    pool.addTask([](){
        sleep(1);
    });

    std::shared_ptr<Threads::Worker> worker = manager->getWorker();

    worker->setTask([](){
        sleep(1);
    });
    Threads::Task task;
    worker->setTask(task);

    worker->isIdle();
    worker->isReserved();

    Threads::Worker* w = new Threads::Worker();

    w->start(Threads::Task([](){
        sleep(1);
    }));

    try {
        w->start(Threads::Task([](){
            sleep(1);
        }));
    } catch (std::runtime_error e) {
        std::cout << "Error catched !" << std::endl;
    }

    delete w;

    w = new Threads::Worker();

    Threads::Task t;

    t = ([](){
        sleep(1);
    });

    w->start(t);

    std::condition_variable cv;
    std::mutex m;
    try {
        w->start(cv, m);
    } catch (std::runtime_error e) {
        register_test(true, "Successfully raised an error when we started two times the same worker");
    }

    pool.stop();

    delete manager;

    return end_test();
}
