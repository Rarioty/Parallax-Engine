#include <Parallax/Parsers/PSF/PSFParser.hpp>
#include <Parallax/Debug/Debug.hpp>

#include <algorithm>
#include <fstream>

namespace Parallax::Parser
{
    int PSFParser::m_version = 10000;

    PSFParser::PSFParser(const std::string& filename)
        : m_sections()
        , m_filename(filename)
    {}

    PSFParser::~PSFParser()
    {
        for (auto it = m_sections.begin(); it != m_sections.end(); ++it)
        {
            it->second.clear();
        }
        m_sections.clear();
    }

    void PSFParser::reset()
    {
        std::ifstream infile(m_filename);
        auto it = m_sections.end();
        std::string line;

        PARALLAX_TRACE("Parsing setting file...");
        PARALLAX_WARN(infile.good(), "Setting file %s cannot be opened !", m_filename.c_str());

        while(std::getline(infile, line))
        {
            if (line[0] == '#')
                continue;
            else if (line[0] == '[')
            {
                // New section
                char newSection[50] = {0};
                sscanf(line.c_str(), "[%s]", newSection);
                std::string section = std::string(newSection);

                section = section.substr(0, section.find("]"));

                PARALLAX_TRACE("New section found %s", section.c_str());
                m_sections.insert(
                    std::pair<
                        std::string,
                        std::map<std::string, std::string>
                    >
                    (
                        section,
                        std::map<std::string, std::string>()
                    )
                );

                it = m_sections.find(section);
                PARALLAX_FATAL(it != m_sections.end(), "WEIRD !");
            }
            else
            {
                std::string name;
                std::string value;

                std::size_t pos = line.find("=");

                if (pos != std::string::npos)
                {
                    name = line.substr(0, pos);
                    value = line.substr(pos+1);
                }
                else
                    continue;

                name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int c){return !std::isspace(c);}));
                name.erase(std::find_if(name.rbegin(), name.rend(), [](int c){return !std::isspace(c);}).base(), name.end());

                value.erase(value.begin(), std::find_if(value.begin(), value.end(), [](int c){return !std::isspace(c);}));
                value.erase(std::find_if(value.rbegin(), value.rend(), [](int c){return !std::isspace(c);}).base(), value.end());

                PARALLAX_TRACE("New setting %s = %s", name.c_str(), value.c_str());

                PARALLAX_FATAL(it != m_sections.end(), "This setting is not in a section (%s) !", name.c_str());

                it->second.insert(
                    std::pair<
                        std::string,
                        std::string
                    >(
                        name,
                        value
                    )
                );
            }
        }
    }

    void PSFParser::sync(void)
    {

    }

    std::string PSFParser::getSetting(const char* key, bool critical)
    {
        std::string sectionName;
        std::string name;
        std::string skey = key;

        std::size_t pos = skey.find(":");

        if (pos != std::string::npos)
        {
            sectionName = skey.substr(0, pos);
            name = skey.substr(pos+1);
        }
        else
        {
            sectionName = "General";
            name = skey;
        }

        auto section = m_sections.find(sectionName);
        if (critical)
        {
            PARALLAX_FATAL(m_sections.end() != section, "Section name doesn't exist (%s)", sectionName.c_str());
        }
        else
        {
            PARALLAX_WARN(m_sections.end() != section, "Section name doesn't exist (%s)", sectionName.c_str());
        }

        if (section == m_sections.end())
            return nullptr;

        auto setting = section->second.find(name);
        if (critical)
        {
            PARALLAX_FATAL(section->second.end() != setting, "Setting doesn't exist in this section (%s in %s)", name.c_str(), sectionName.c_str());
        }
        else
        {
            PARALLAX_WARN(section->second.end() != setting, "Setting doesn't exist in this section (%s in %s)", name.c_str(), sectionName.c_str());
        }

        if (setting == section->second.end())
            return nullptr;

        return setting->second;
    }
}
