#include <PIL/fs/fs.hpp>

#include <tests.hpp>
#include <iostream>
#include <fstream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    fs::File f = fs::open("test");
    std::string test;

    if (f.exists())
        return 0;

    auto out = f.createOutputStream();

    *out << "test" << std::endl;

    auto in = f.createInputStream();

    *in >> test;

    register_test(test == "test", "Correct string retrieved");

    register_test(f.remove(), "File successfully removed");

    return end_test();
}
