#include <Parallax/FS/URL.hpp>

#include <tests.hpp>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    FS::Url tmp;
    FS::Url url(tmp);

    url = FS::Url("ssh://testuser:testpass@testdomain.com:22/test/full/path?testquery=3&test2=5#testfragment");

    std::cout << "URL: " << url.toString() << std::endl;
    std::cout << "Scheme: " << url.scheme() << std::endl;
    std::cout << "Location: " << url.location() << std::endl;
    std::cout << "Address: " << url.address() << std::endl;
    std::cout << "Host: " << url.host() << std::endl;
    std::cout << "Path: " << url.path() << std::endl;
    std::cout << "Query: " << url.query() << std::endl;
    std::cout << "Fragment: " << url.fragment() << std::endl;
    std::cout << "Login: " << url.login() << std::endl;
    std::cout << "User: " << url.username() << std::endl;
    std::cout << "Pass: " << url.password() << std::endl;
    std::cout << "Port: " << url.port() << std::endl;

    return end_test();
}
