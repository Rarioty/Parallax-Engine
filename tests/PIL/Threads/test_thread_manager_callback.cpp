#include <Parallax/Threads/ThreadManager.hpp>
#include <Parallax/Threads/ThreadPool.hpp>

#include <tests.hpp>
#include <unistd.h>
#include <iostream>

using namespace Parallax;

int result = 0;
int callback = 0;

int main(int argc, char* argv[])
{
    Threads::ThreadManager manager(1);
    Threads::ThreadPool pool(2, manager);

    pool.start();

    Threads::Task t;

    t = ([](){
        sleep(1);
        result = 1;
    });

    t.addCallback([](){
        std::cout << "Callback called :D" << std::endl;
        callback = 1;
    });

    pool.addTask(t);

    pool.stop();

    register_test(result == 1 && callback == 1, "Function ended and callback called !");

    return end_test();
}
