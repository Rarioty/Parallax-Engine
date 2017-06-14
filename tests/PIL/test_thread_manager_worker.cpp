#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Threads/ThreadPool.hpp>
#include <PIL/Threads/Worker.hpp>

#include <tests.hpp>
#include <unistd.h>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    int ret = 0;

    Threads::ThreadManager* manager = new Threads::ThreadManager(1);
    Threads::ThreadPool pool(2, *manager);

    pool.start();

    pool.addTask([](){
        sleep(2);
    });

    std::shared_ptr<Threads::Worker> worker = manager->getWorker();

    worker->setTask([](){
        sleep(2);
    });
    worker->setTask(Threads::Task());

    worker->isIdle();
    worker->isReserved();

    pool.stop();

    delete manager;

    return ret;
}
