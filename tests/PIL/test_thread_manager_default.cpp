#include <PIL/Threads/ThreadManager.hpp>
#include <PIL/Threads/ThreadPool.hpp>

#include <tests.hpp>

using namespace Parallax;

int main(int argc, char* argv[])
{
    int ret = 0;

    Threads::ThreadManager manager(1);
    Threads::ThreadPool pool(2, manager);

    pool.start();

    auto future = pool.addTask([](const std::string& ret) { return ret; }, "success");

    std::cout << future.get() << std::endl;

    pool.stop();

    return ret;
}
