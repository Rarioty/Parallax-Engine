#ifndef PARALLAX_PSFPARSER_HPP_GUARD
#define PARALLAX_PSFPARSER_HPP_GUARD

#include <Parallax/Types.hpp>
#include <sstream>
#include <string>
#include <map>

namespace Parallax
{
    namespace Parser
    {
        class PSFParser
        {
        public:
            PSFParser(const std::string& filename);
            ~PSFParser();

        public:
            template <typename T>
            T getAs(const char* key)
            {
                return convertAndSendBack<T>(key, false);
            }
            template <typename T>
            T getAsCritical(const char* key)
            {
                return convertAndSendBack<T>(key, true);
            }

            void            reset();
            void            sync(void);

        private:
            template <typename T>
            T convertAndSendBack(const char* key, bool critical)
            {
                std::string value = getSetting(key, critical);

                std::stringstream ss(value);
                T result;
                return (ss >> result) ? result : 0;
            }

            std::string     getSetting(const char* key, bool critical);

        private:
            typedef std::map<std::string, std::string> Settings;

            static int                              m_version;
            std::map<std::string, Settings>         m_sections;
            std::string                             m_filename;
        };
    }
}

#endif
