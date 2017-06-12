#include <PIL/Types.hpp>
#include <tests.hpp>

#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    I8      integer_8;
    I16     integer_16;
    I32     integer_32;
    I64     integer_64;
    U8      unsigned_8;
    U16     unsigned_16;
    U32     unsigned_32;
    U64     unsigned_64;

    start_test("Fixed size types");

    register_test(sizeof(integer_8) == 1, "Size of I8  == 8");
    register_test(sizeof(integer_16) == 2, "Size of I16 == 2");
    register_test(sizeof(integer_32) == 4, "Size of I32 == 4");
    register_test(sizeof(integer_64) == 8, "Size of I64 == 8");

    register_test(sizeof(unsigned_8) == 1, "Size of U8  == 8");
    register_test(sizeof(unsigned_16) == 2, "Size of U16 == 2");
    register_test(sizeof(unsigned_32) == 4, "Size of U32 == 4");
    register_test(sizeof(unsigned_64) == 8, "Size of U64 == 8");

    return end_test();
}
