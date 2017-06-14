#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Threads/ThreadPool.hpp>

#include <unistd.h>

using namespace Parallax;

int main(int argc, char* argv[])
{
    int ret = 1;

    Threads::ThreadManager manager(1);
    Threads::ThreadPool* pool;
    std::pair<bool, std::string> result;

    try {
        pool = new Threads::ThreadPool(0, manager);
    } catch(std::invalid_argument ex) {
        ret = 0;
    }

    pool = new Threads::ThreadPool(2, manager);
    pool->start();

    delete pool;

    pool = new Threads::ThreadPool(2, manager);
    pool->stop();
    result = pool->start();

    ret |= not result.first;

    pool->stop();
    result = pool->pause();

    ret |= result.first;

    pool->start();
    result = pool->unpause();

    ret |= result.first;

    pool->stop();
    result = pool->stop();

    ret |= result.first;

    pool->resize(4);

    pool->stop();
    try {
        pool->addTask(Threads::Task());
    } catch (std::runtime_error e) {
        ret |= 0;
    }

    pool->start();
    Threads::Task t([](){
        sleep(2);
    });
    pool->addTask([](){
        sleep(2);
    });

    pool->stop();

    manager.stop();
    manager.getWorker();

    manager.stop();

    return ret;
}
