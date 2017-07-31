#ifndef PARALLAX_SETTINGS_HPP_GUARD
#define PARALLAX_SETTINGS_HPP_GUARD

#include <Parallax/Parsers/PSF/PSFParser.hpp>
#include <Parallax/Types.hpp>
#include <string>

namespace Parallax
{
    namespace Settings
    {
#ifdef PARALLAX_SETTINGS_CPP
        Parser::PSFParser           s_settings("settings.psf");
#else
        extern Parser::PSFParser    s_settings;
#endif

        void  loadSettings();

        template <typename T>
        T getAs(const char* key)
        {
            return s_settings.getAs<T>(key);
        }

        template <typename T>
        T getAsCritical(const char* key)
        {
            return s_settings.getAsCritical<T>(key);
        }
    }
}

#endif
