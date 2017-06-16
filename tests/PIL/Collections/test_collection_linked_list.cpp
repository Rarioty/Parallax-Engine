#include <tests.hpp>

#include <PIL/Collections/LinkedList.hpp>

using namespace Parallax::Collections;

int main(int argc, char* argv[])
{
    LinkedList<int> list;

    list.push(2);
    list.push(3);
    list.push(4);

    register_test(list.size() == 3, "Correct size");
    register_test(list.get(0) == 2, "Correct element returned");

    try {
        list.get(4);
    } catch (std::runtime_error e) {
        register_test(true, "Error raised when accessing too far position");
    }

    list.remove(1);

    register_test(list.size() == 2, "Correct size after removal");

    list.remove(0);

    register_test(list.get(0) == 4, "Correct value after removal");

    list.push(10);

    register_test(list.size() == 2, "Correct size after repushing item");

    register_test(list.get(0) == 4 && list.get(1) == 10, "Correct order");

    return end_test();
}
