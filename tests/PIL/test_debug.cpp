#include <Parallax/Debug/Debug.hpp>
#include <tests.hpp>

#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    Debug::Init();

    PARALLAX_TRACE("trace");
    PARALLAX_CHECK(true, "check");
    PARALLAX_WARN(true, "warn");
    PARALLAX_FATAL(true, "fatal");

    return end_test();
}
