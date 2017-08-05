#include <Parallax/Renderers/Renderer.hpp>

#include <Parallax/Window.hpp>

#include <tests.hpp>
#include <iostream>

using namespace Parallax;

int main(int argc, char* argv[])
{
    register_test(createWindow("test", 1024, 768, 0), "Window created");

    Renderer::Init("opengl", 1024, 768);

    std::cout << "Renderer name: " << Renderer::GetRendererName() << std::endl;
    std::cout << "Renderer type: " << Renderer::GetRendererType() << std::endl;
    std::cout << "Is device removed: " << Renderer::IsDeviceRemoved() << std::endl;

    Renderer::Shutdown();

    return end_test();
}
