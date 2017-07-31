#include <Parallax/Debug/Debug.hpp>

#define PARALLAX_SETTINGS_CPP
#include <Parallax/Settings.hpp>

#include <map>

namespace Parallax::Settings
{
    void loadSettings()
    {
        s_settings.reset();
    }
}
