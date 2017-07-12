#include <Parallax/Collections/LinkedList.hpp>

#include <tests.hpp>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Collections::LinkedList<int> list;

    list.push_back(0);
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    Collections::LinkedList<int>::Iterator it;

    std::cout << "Printing list..." << std::endl;
    for(it = list.begin(); it != list.end(); ++it)
    {
        std::cout << *it << ", ";
    }

    std::cout << std::endl << "Again..." << std::endl;
    for (it = list.begin(); it != list.end(); it.next())
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    register_test(it == list.end(), "Successfully ended loop");

    return end_test();
}
