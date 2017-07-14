#include <Parallax/Parallax.hpp>

std::string getParallaxVersion()
{
    return std::string(PARALLAX_API_VERSION) + std::string(".") + std::string(PARALLAX_MAKE_DATE) + std::string(PARALLAX_MAKE_HOUR);
}
