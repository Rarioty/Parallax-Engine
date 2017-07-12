#include <Parallax/Collections/Stack.hpp>

#include <tests.hpp>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Collections::Stack<int>* stack;
    int ret, i;

    ret = 0;
    try {
        stack = new Collections::Stack<int>(0);
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when trying to create a zero element stack");

    stack = new Collections::Stack<int>();

    ret = 0;
    try {
        stack->top();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when trying to get an element from an empty stack");

    ret = 0;
    try {
        stack->pop();
    } catch (std::runtime_error e) {
        ret = 1;
    }
    register_test(ret == 1, "Successfully raised an error when trying to pop an empty stack");

    register_test(stack->empty(), "Stack empty");

    stack->push(0);
    stack->push(1);
    stack->push(2);

    register_test(!stack->empty(), "Stack non empty");
    register_test(stack->size() == 3, "Correct size for the stack");

    register_test(stack->top() == 2, "Correct element on the top");

    register_test(stack->pop() == 2, "Correct value returned when pop");

    register_test(stack->top() == 1, "Correct element on the top after pop");

    stack->pop();
    stack->pop();

    for (i = 0; i < 60; ++i)
    {
        stack->push(i);
    }

    register_test(stack->size() == 60, "Correct size after array resizing");

    delete stack;

    return end_test();
}
