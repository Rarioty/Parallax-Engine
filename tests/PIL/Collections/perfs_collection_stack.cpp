#include <PIL/Collections/Stack.hpp>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <stack>

using namespace Parallax;

int main(int argc, char *argv[])
{
    std::chrono::duration<double> elapsedStd;
    std::chrono::duration<double> elapsedParallax;
    Collections::Stack<int>* stack;
    std::stack<int>* stdstack;
    U32 i;

    // Header
    std::cout << "| Test name   | Nb elements |    Std time   | Parallax time |" << std::endl;
    std::cout << "|-------------+-------------+---------------+---------------|" << std::endl;

    /*********************************************************************************************
     * Push
     ********************************************************************************************/
    stack = new Collections::Stack<int>();
    stdstack = new std::stack<int>();

    auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stdstack->push(i);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| push        | 1 000 000   | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stack->push(i);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete stack;
    delete stdstack;

    /*********************************************************************************************
     * Pop
     ********************************************************************************************/
    stack = new Collections::Stack<int>();
    stdstack = new std::stack<int>();

    for (i = 0; i < 1000000; ++i)
    {
        stdstack->push(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stdstack->pop();
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| pop         | 1 000 000   | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    for (i = 0; i < 1000000; ++i)
    {
        stack->push(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stack->pop();
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete stack;
    delete stdstack;

    return 0;
}
