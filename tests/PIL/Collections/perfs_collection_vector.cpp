#include <Parallax/Collections/Vector.hpp>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

using namespace Parallax;

int main(int argc, char* argv[])
{
    std::chrono::duration<double> elapsedStd;
    std::chrono::duration<double> elapsedParallax;
    Collections::Vector<int>* vector;
    std::vector<int>* stdvector;
    U32 i;

    // Header
    std::cout << "| Test name   | Nb elements |    Std time   | Parallax time |" << std::endl;
    std::cout << "|-------------+-------------+---------------+---------------|" << std::endl;

    /*********************************************************************************************
     * Push_front
     ********************************************************************************************/
    vector = new Collections::Vector<int>();
    stdvector = new std::vector<int>();

    auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stdvector->push_back(i);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| push_back   | 1 000 000   | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        vector->push_back(i);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete vector;
    delete stdvector;

    /*********************************************************************************************
     * Multiply all by two
     ********************************************************************************************/
    vector = new Collections::Vector<int>();
    stdvector = new std::vector<int>();

    for (i = 0; i < 1000000; ++i)
    {
        stdvector->push_back(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stdvector->at(i) *= 2;
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| multiply    | 1 000 000   | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    for (i = 0; i < 1000000; ++i)
    {
        vector->push_back(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        vector->at(i) *= 2;
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete vector;
    delete stdvector;

    /*********************************************************************************************
     * Pop back
     ********************************************************************************************/
    vector = new Collections::Vector<int>();
    stdvector = new std::vector<int>();

    for (i = 0; i < 1000000; ++i)
    {
        stdvector->push_back(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stdvector->pop_back();
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| pop_back    | 1 000 000   | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    for (i = 0; i < 1000000; ++i)
    {
        vector->push_back(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        vector->pop_back();
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete vector;
    delete stdvector;

    return 0;
}
