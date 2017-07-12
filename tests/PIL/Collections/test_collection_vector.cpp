#include <Parallax/Collections/Vector.hpp>

#include <tests.hpp>
#include <iostream>
#include <time.h>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Collections::Vector<int>* vector;
    int ret;
    U32 i;

    srand(time(NULL));

    ret = 0;
    try {
        vector = new Collections::Vector<int>(0);
    } catch (std::runtime_error e) {
        ret = 1;
    }

    register_test(ret == 1, "Successfully raise an error when creating vector of size 0");

    vector = new Collections::Vector<int>();

    for (i = 0; i < 40; ++i)
    {
        vector->push_front(i);
    }

    delete vector;

    vector = new Collections::Vector<int>();

    for (i = 0; i < 40; ++i)
    {
        vector->push_back(i);
    }

    delete vector;

    vector = new Collections::Vector<int>();

    vector->insert(0, 0);
    vector->insert(1, 40);
    vector->insert(2, 1000);

    register_test(vector->size() == 1001, "Size successfully computed");

    delete vector;

    vector = new Collections::Vector<int>();

    ret = 0;
    try {
        vector->resize(10);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when resizing with a smaller size");

    vector->resize(32);
    vector->resize(40);

    for (i = 0; i < 40; ++i)
    {
        vector->push_back(i);
    }

    ret = 0;
    try {
        vector->remove(100);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when removing too far element");

    vector->remove(39);
    vector->remove(15);

    vector->remove([](U32 position, int value){
        return value % 2 == 0;
    });

    delete vector;

    vector = new Collections::Vector<int>();

    vector->push_back(0);
    vector->push_back(1);
    vector->push_back(2);
    vector->push_back(3);
    vector->push_back(4);

    register_test(vector->get(2) == 2, "Successfully returned the right element");

    ret = 0;
    try {
        vector->get(10);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when accessing too far element");

    vector->remove([](U32 position, int value){
        return true;
    });

    ret = 0;
    try {
        vector->front();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when asking front on a zero element vector");

    ret = 0;
    try {
        vector->back();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when asking back on a zero element vector");

    ret = 0;
    try {
        vector->at(10);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when asking reference on a zero element vector");

    vector->push_back(0);
    vector->push_back(1);

    register_test(vector->front() == 0, "Front returned the correct value");
    register_test(vector->back() == 1, "Back returned the correct value");
    register_test(vector->at(0) == 0, "At returned the correct value");

    vector->pop_back();
    vector->pop_back();

    ret = 0;
    try {
        vector->pop_back();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when popping back a zero element container");

    delete vector;

    vector = new Collections::Vector<int>();

    vector->execute([](U32 position, int* element){
        *element += 1;
    });
    vector->execute((std::function<bool(U32, int*)>)[](U32 position, int* element){
        return true;
    });

    vector->push_back(0);
    vector->push_back(1);
    vector->push_back(2);

    vector->execute([](U32 position, int* element){
        *element += 1;
    });

    register_test(vector->get(0) == 1 && vector->get(1) == 2 && vector->get(2) == 3, "Function successfully executed");

    vector->execute((std::function<bool(U32, int*)>)[](U32 position, int* element){
        *element += 1;
        return position != 1;
    });

    register_test(vector->get(0) == 2 && vector->get(1) == 3 && vector->get(2) == 3, "Function successfully executed *2");

    int random = vector->random();

    std::cout << "Get randomed value: " << random << std::endl;

    vector->remove(0);
    vector->remove(0);
    vector->remove(0);

    ret = 0;
    try {
        vector->random();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when asking for a random element on a zero element vector");

    delete vector;

    vector = new Collections::Vector<int>();

    vector->push_back(0);
    vector->push_back(1);
    vector->push_back(2);
    vector->push_back(3);
    vector->push_back(1);
    vector->push_back(4);

    std::pair<bool, U32> result;

    result = vector->find(10);

    register_test(!result.first, "Successfully returned false when asking to find a non existing value");

    result = vector->find(0);

    register_test(result.first && result.second == 0, "Successfully find the value");

    result = vector->find(3);

    register_test(result.first && result.second == 3, "Successfully find the value *2");

    result = vector->find_back(10);

    register_test(!result.first, "Successfully returned false when asking to find a non existing value from the back");

    result = vector->find_back(4);

    register_test(result.first && result.second == 5, "Successfully find the value from the back");

    result = vector->find_back(3);

    result = vector->find_back(0);

    register_test(result.first && result.second == 0, "Successfully find the value from the back *2");

    std::pair<U32, U32*> multiple_results;

    multiple_results = vector->find_all(10);

    register_test(multiple_results.first == 0, "Successfully returned false when asking to find (all) a non existing value");

    multiple_results = vector->find_all(1);

    register_test(multiple_results.first == 2, "Successfully found all values");

    delete multiple_results.second;

    multiple_results = vector->find_all([](U32 position, int* value){
        return *value == 1;
    });

    register_test(multiple_results.first == 2, "Successfully found all values with function");

    vector->find_all([](U32 position, int* value){
        return *value == 10;
    });

    delete multiple_results.second;

    delete vector;

    vector = new Collections::Vector<int>();

    vector->push_back(5);
    vector->push_back(-3);
    vector->push_back(7);
    vector->push_back(2);
    vector->push_back(-12);

    vector->sort([](int first, int second){
        return first < second;
    });

    int tmp = vector->get(0);
    ret = 1;
    for (i = 1; i < vector->size(); ++i)
    {
        if (vector->get(i) < tmp)
            ret = 0;

        tmp = vector->get(i);
    }

    register_test(ret == 1, "Successfully sorted the vecctor");

    delete vector;

    return end_test();
}
