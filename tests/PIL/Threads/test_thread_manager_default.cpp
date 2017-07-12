#include <Parallax/Threads/ThreadManager.hpp>
#include <Parallax/Threads/ThreadPool.hpp>

#include <tests.hpp>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Threads::ThreadManager manager(1);
    Threads::ThreadPool pool(2, manager);

    pool.start();

    auto future = pool.addTask([](int number) { return number * 2; }, 21);

    int result = future.get();

    std::cout << "Result: " << result << std::endl;

    register_test(result == 42, "Function well executed !");

    pool.stop();

    return end_test();
}
