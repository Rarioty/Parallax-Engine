#include <Parallax/Parallax.hpp>

std::string getParallaxVersion()
{
    return std::string(PARALLAX_VERSION_MAJOR) + std::string(".") + std::string(PARALLAX_VERSION_MINOR) + std::string(".")
        + std::string(PARALLAX_MAKE_DATE) + std::string(PARALLAX_MAKE_HOUR);
}
