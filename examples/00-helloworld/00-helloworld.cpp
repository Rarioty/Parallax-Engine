#include <Parallax/Parallax.hpp>
#include <Parallax/Window.hpp>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
	if (Parallax::init("00-helloworld"))
	{
		Parallax::launch();
		Parallax::shutdown();
	}
	else
		std::cerr << "Can't initialize Parallax !" << std::endl;

    return 0;
}
