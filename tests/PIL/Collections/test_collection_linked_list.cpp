#include <tests.hpp>

#include <PIL/Collections/LinkedList.hpp>
#include <iostream>
#include <time.h>

using namespace Parallax::Collections;
using namespace Parallax;

int main(int argc, char* argv[])
{
    LinkedList<int> list;
    int ret;

    srand(time(NULL));

    // Testing push_front
    list.push_front(0);
    list.push_front(1);

    register_test(list.get(0) == 1, "Correct value after push_front");

    // Testing push_back
    list.remove(0);
    list.remove(0);
    list.push_back(0);
    list.push_back(1);

    register_test(list.get(0) == 0, "Correct value after push_back");

    // Testing insert
    list.remove(0);
    list.remove(0);
    list.insert(0, 0);
    list.insert(1, 3);
    list.insert(2, 1);
    list.insert(3, 1);

    register_test(list.get(1) == 3, "Correct value after insert");

    // Testing size
    list.size();
    register_test(list.size() == 4, "Correct size");
    list.remove(0);
    list.remove(0);
    list.remove(0);
    list.remove(0);
    list.size();
    register_test(list.size() == 0, "Correct size *2");

    // Testing remove
    list.push_front(0);
    list.push_front(1);
    list.remove([](U32 pos, int element){
        return element == 1;
    });
    register_test(list.size() == 1, "Element successfully removed");

    list.push_front(0);
    list.push_front(0);
    list.remove(1);
    list.remove(1);
    list.remove(0);

    ret = 0;
    try {
        list.remove(0);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Error successfully raised when removing element in an empty list");

    list.push_front(0);
    ret = 0;
    try {
        list.remove(5);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Error successfully raised when removing element too far");

    //Testing get
    list.push_front(1);
    list.get(0);
    list.get(1);
    ret = 0;
    try {
        list.get(5);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Error successfully raised when getting too far element");

    register_test(list.front() == 1, "Front works");
    register_test(list.back() == 0, "Back works");

    list.remove(0);
    list.remove(0);

    ret = 0;
    try {
        list.front();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Error successfully raised when asking for front but the list is empty");

    ret = 0;
    try {
        list.back();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Error successfully raised when asking for back but the list is empty");

    // Testing execute
    list.execute([](U32 current, int* element){

    });
    list.push_front(0);
    list.execute([](U32 current, int* element) {
        register_test(true, "Execution successfully works");
    });

    list.execute((std::function<bool(U32, int*)>)[](U32 current, int* element) {
        return true;
    });
    list.execute((std::function<bool(U32, int*)>)[](U32 current, int* element) {
        return false;
    });
    list.remove(0);
    list.execute((std::function<bool(U32, int*)>)[](U32 current, int* element) {
        return true;
    });
    list.execute((std::function<bool(U32, int*)>)[](U32 current, int* element) {
        return false;
    });

    ret = 0;
    try {
        list.random();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Error successfully raised when random is called but the list is empty");

    list.push_front(0);
    list.random();
    list.push_front(1);
    list.push_front(2);
    int random = list.random();
    list.random();
    list.random();
    list.random();
    list.random();

    std::cout << "Random number get is " << random << std::endl;

    list.find(2);
    list.find(1);
    list.find(5);

    list.find_back(0);
    list.find_back(1);
    list.find_back(2);
    list.find_back(5);

    std::pair<bool, U32*> result;

    result = list.find_all(2);
    delete result.second;

    result = list.find_all([](U32 pos, int* element){
        return true;
    });
    delete result.second;
    result = list.find_all([](U32 pos, int* element){
        return pos == 0;
    });
    delete result.second;

    result = list.find_all([](U32 pos, int* element){
        return false;
    });

    list.sort([](int* first, int* second){
        return *first < *second;
    });

    return end_test();
}
