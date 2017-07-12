#include <Parallax/fs/Path.hpp>

#include <Parallax/Collections/Vector.hpp>
#include <Parallax/Parallax.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>

namespace Parallax::fs
{
    Path::Path()
        : m_path("")
        , m_pointsToContent(false)
        , m_details(false)
    {}

    Path::Path(const Path& path)
        : m_path(path.m_path)
        , m_pointsToContent(path.m_pointsToContent)
        , m_details(path.m_details)
        , m_fullPath(path.m_fullPath)
        , m_filename(path.m_filename)
        , m_basename(path.m_basename)
        , m_extension(path.m_extension)
        , m_directoryPath(path.m_directoryPath)
        , m_driveLetter(path.m_driveLetter)
        , m_absolute(path.m_absolute)
    {}

    Path::Path(const std::string& path)
        : m_pointsToContent(false)
        , m_details(false)
    {
        setPath(path);
    }

    Path::Path(const char* path)
        : m_pointsToContent(false)
        , m_details(false)
    {
        setPath(path);
    }

    Path::~Path()
    {}

    Path& Path::operator=(const Path& path)
    {
        m_path              = path.m_path;
        m_pointsToContent   = path.m_pointsToContent;
        m_details           = path.m_details;
        m_fullPath          = path.m_fullPath;
        m_filename          = path.m_filename;
        m_basename          = path.m_basename;
        m_extension         = path.m_extension;
        m_directoryPath     = path.m_directoryPath;
        m_driveLetter       = path.m_driveLetter;
        m_absolute          = path.m_absolute;

        return *this;
    }

    const std::string& Path::path() const
    {
        return m_path;
    }

    void Path::setPath(const std::string& path)
    {
        m_path = path;

        m_pointsToContent = false;
        m_details         = false;
        m_fullPath        = "";
        m_filename        = "";
        m_basename        = "";
        m_extension       = "";
        m_directoryPath   = "";
        m_driveLetter     = "";
        m_absolute        = false;

        std::replace(m_path.begin(), m_path.end(), '\\', '/');

        auto pos = m_path.find_last_of("/");
        if (pos == m_path.size() - 1)
        {
            m_pointsToContent = true;
        }
    }

    std::string Path::toNative() const
    {
        auto path = m_path;

#ifdef PARALLAX_BUILD_SYSTEM_WIN32
        std::replace(path.begin(), path.end(), "/", "\\");
#endif

        return path;
    }

    bool Path::isEmpty() const
    {
        return m_path.empty();
    }

    bool Path::pointsToContents() const
    {
        return m_pointsToContent;
    }

    const std::string& Path::fullPath()
    {
        analyze();

        return m_fullPath;
    }

    const std::string& Path::filename()
    {
        analyze();

        return m_filename;
    }

    const std::string& Path::basename()
    {
        analyze();

        return m_basename;
    }

    const std::string& Path::extension()
    {
        analyze();

        return m_extension;
    }

    const std::string& Path::directoryPath()
    {
        analyze();

        return m_directoryPath;
    }

    const std::string& Path::driveLetter()
    {
        analyze();

        return m_driveLetter;
    }

    bool Path::isAbsolute()
    {
        analyze();

        return m_absolute;
    }

    bool Path::isRelative()
    {
        analyze();

        return !m_absolute;
    }

    Path Path::resolve(Path path)
    {
        if (path.isEmpty() && isEmpty())
        {
            return Path();
        }

        if (path.isAbsolute() || isEmpty())
        {
            return path;
        }

        if (path.isEmpty())
        {
            return *this;
        }

        return Path(fullPath() + "/" + path.path());
    }

    std::string Path::resolved() const
    {
        Collections::Vector<std::string> parts;
        std::stringstream ss(m_path);

        std::string name;
        while (std::getline(ss, name, '/'))
        {
            parts.push_back(name);
        }

        Collections::Vector<std::string> stack;
        size_t removableItems = 0;
        bool absolute = false;

        size_t numParts = parts.size();
        for (size_t i = 0; i < numParts; ++i)
        {
            const std::string& path = parts.at(i);

            if (i == 0 && (path.empty() || (path.length() == 2 && path[1] == ':')))
            {
                absolute = true;
            }

            if (path == ".")
            {
                continue;
            }
            else if (path == ".." && removableItems > 0)
            {
                stack.pop_back();
                removableItems--;
            }
            else
            {
                stack.push_back(path);

                if (!(i == 0 && absolute) && path != "..")
                {
                    removableItems++;
                }
            }
        }

        std::string resolved;

        for (size_t i = 0; i < stack.size(); ++i)
        {
            resolved += stack.at(i);

            if (i + 1 < stack.size() || (i == 0 && absolute))
            {
                resolved += "/";
            }
        }

        if (resolved.empty())
            return ".";

        return resolved;
    }

    void Path::analyze()
    {
        if (m_details)
            return;

        m_fullPath      = "";
        m_filename      = "";
        m_basename      = "";
        m_extension     = "";
        m_directoryPath = "";
        m_driveLetter   = "";
        m_absolute      = false;

        Collections::Vector<std::string> parts;
        std::stringstream ss(m_path);

        std::string name;
        while (std::getline(ss, name, '/'))
        {
            parts.push_back(name);
        }

        size_t numParts = parts.size();

        for (size_t i = 0; i < numParts; ++i)
        {
            const std::string& path = parts.at(i);

            if (i == 0 && (path.empty() || (path.length() == 2 && path[1] == ':')))
            {
                parts.at(i) += "/";
                m_absolute = true;
            }
            else if (i < numParts - 1)
            {
                parts.at(i) += "/";
            }
        }

        m_filename = (numParts > 0) ? parts.at(numParts-1) : "";

        m_directoryPath = "";

        if (numParts > 1)
        {
            for (size_t i = 0; i < numParts - 1; ++i)
            {
                m_directoryPath += parts.at(i);
            }

            m_fullPath = m_directoryPath + m_filename;
        }
        else if (numParts == 1 && m_absolute)
        {
            m_directoryPath = parts.at(0);
            m_fullPath = m_directoryPath;
        }
        else if (numParts == 1)
        {
            m_fullPath = m_filename;
        }

        size_t pos = m_filename.find_first_of('.', 1);

        if (m_filename == "." || m_filename == ".." || pos == std::string::npos)
        {
            m_basename = m_filename;
            m_extension = "";
        }
        else
        {
            m_basename = m_filename.substr(0, pos);
            m_extension = m_filename.substr(pos);
        }

        pos = m_fullPath.find_first_of(':');

        m_driveLetter = pos == 1 ? m_path.substr(0, pos+1) : "";

        m_details = true;
    }
}
