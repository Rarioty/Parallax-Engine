#include <tests.hpp>

#include <iostream>

int nb_total_tests = 0;
int nb_valid_tests = 0;

void start_test(const char* name)
{
    std::cout << "=== Starting test: " << name << std::endl;
}

void register_test(int valid, const char* test)
{
    nb_total_tests++;
    if (valid)
    {
        nb_valid_tests++;
    }

    if (!valid)
    {
        std::cout << "FAILED:\t" << test << std::endl;
    }
    else
    {
        std::cout << "SUCCESS:\t" << test << std::endl;
    }
}

int end_test()
{
    std::cout << "=== Final score: " << nb_valid_tests << "/" << nb_total_tests << std::endl;
    std::cout << "=> " << (nb_valid_tests == nb_total_tests ? "SUCCESS" : "FAILED") << std::endl;

    return (nb_valid_tests == nb_total_tests ? 0 : 1);
}
