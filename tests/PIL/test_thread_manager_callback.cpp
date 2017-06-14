#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Threads/ThreadPool.hpp>

#include <tests.hpp>
#include <unistd.h>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    int ret = 0;

    Threads::ThreadManager manager(1);
    Threads::ThreadPool pool(2, manager);

    pool.start();

    Threads::Task t;

    t = ([](){
        sleep(2);
    });

    t.addCallback([](){
        std::cout << "Callback called :D" << std::endl;
    });

    pool.addTask(t);

    pool.stop();

    return ret;
}
