#include <PIL/Collections/Vector.hpp>

#include <tests.hpp>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Collections::Vector<int> vector;

    vector.push_back(0);
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    vector.push_back(4);

    Collections::Vector<int>::Iterator it;

    std::cout << "Printing vector..." << std::endl;
    for(it = vector.begin(); it != vector.end(); ++it)
    {
        std::cout << *it << ", ";
    }

    std::cout << std::endl << "Again..." << std::endl;
    for (it = vector.begin(); it != vector.end(); it.next())
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    register_test(it == vector.end(), "Successfully ended loop");

    return end_test();
}
