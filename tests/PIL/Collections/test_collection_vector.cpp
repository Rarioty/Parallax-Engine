#include <PIL/Collections/Vector.hpp>

#include <tests.hpp>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Collections::Vector<int>* vector;
    int ret;

    ret = 0;
    try {
        vector = new Collections::Vector<int>(0);
    } catch (std::runtime_error e) {
        ret = 1;
    }

    register_test(ret == 1, "Successfully raise an error when creating vector of size 0");

    vector = new Collections::Vector<int>();

    return end_test();
}
