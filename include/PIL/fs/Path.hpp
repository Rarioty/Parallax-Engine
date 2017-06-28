#ifndef PATH_HPP
#define PATH_HPP

#include <string>

namespace Parallax
{
    namespace fs
    {
        class Path
        {
        public:
            Path();
            Path(const Path& path);
            Path(const std::string& path);
            Path(const char* path);
            ~Path();

            Path& operator=(const Path& path);

            const std::string& path() const;
            void setPath(const std::string& path);

            std::string toNative() const;

            bool isEmpty() const;
            bool pointsToContents() const;
            const std::string& fullPath();

            const std::string& filename();
            const std::string& basename();
            const std::string& extension();
            const std::string& directoryPath();
            const std::string& driveLetter();

            bool isAbsolute();
            bool isRelative();

            Path resolve(Path path);
            std::string resolved() const;

        private:
            void analyze();

        private:
            std::string     m_path;
            bool            m_pointsToContent;

            bool            m_details;
            std::string     m_fullPath;
            std::string     m_filename;
            std::string     m_basename;
            std::string     m_extension;
            std::string     m_directoryPath;
            std::string     m_driveLetter;
            bool            m_absolute;
        };
    }
}

#endif
