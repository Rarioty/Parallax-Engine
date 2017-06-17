#include <PIL/Collections/LinkedList.hpp>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <list>

using namespace Parallax;

int main(int argc, char *argv[])
{
    std::chrono::duration<double> elapsedStd;
    std::chrono::duration<double> elapsedParallax;
    Collections::LinkedList<int>* list;
    std::list<int>* stdlist;
    U32 i;

    // Header
    std::cout << "| Test name   | Nb elements |    Std time   | Parallax time |" << std::endl;
    std::cout << "|-------------+-------------+---------------+---------------|" << std::endl;

    /*********************************************************************************************
     * Push_front
     ********************************************************************************************/
    list = new Collections::LinkedList<int>();
    stdlist = new std::list<int>();

    auto start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stdlist->push_front(i);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| push_front  | 1 000 000   | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        list->push_front(i);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete list;
    delete stdlist;

    /*********************************************************************************************
     * Push_back
     ********************************************************************************************/
    list = new Collections::LinkedList<int>();
    stdlist = new std::list<int>();

    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        stdlist->push_back(i);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| push_back   | 1 000 000   | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 1000000; ++i)
    {
        list->push_back(i);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete list;
    delete stdlist;

    /*********************************************************************************************
     * remove i%2 == 0
     ********************************************************************************************/
    list = new Collections::LinkedList<int>();
    stdlist = new std::list<int>();

    for (i = 0; i < 10000; ++i)
    {
        stdlist->push_back(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (i = 0; i < 5000; ++i)
    {
        stdlist->remove(i*2);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| remove half | 10 000      | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    for (i = 0; i < 10000; ++i)
    {
        list->push_back(i);
    }
    start = std::chrono::high_resolution_clock::now();
    list->remove([](U32 position, int element){
        return element % 2 == 0;
    });
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete list;
    delete stdlist;

    /*********************************************************************************************
     * Iterator traversal
     ********************************************************************************************/
    list = new Collections::LinkedList<int>();
    stdlist = new std::list<int>();

    for (i = 0; i < 100000; ++i)
    {
        stdlist->push_back(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (std::list<int>::iterator it = stdlist->begin(); it != stdlist->end(); ++it)
    {
        (*it) + 1;
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedStd = finish - start;

    std::cout << "| iterate     | 1 000 000   | "
        << std::setw(11) << std::setfill(' ') << elapsedStd.count() << " s | ";

    for (i = 0; i < 100000; ++i)
    {
        list->push_back(i);
    }
    start = std::chrono::high_resolution_clock::now();
    for (Collections::LinkedList<int>::Iterator it = list->begin(); it != list->end(); ++it)
    {
        (*it) + 1;
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsedParallax = finish - start;

    // Printing values
    std::cout << std::setw(11) << std::setfill(' ') << elapsedParallax.count() << " s |" << std::endl;

    delete list;
    delete stdlist;

    return 0;
}
