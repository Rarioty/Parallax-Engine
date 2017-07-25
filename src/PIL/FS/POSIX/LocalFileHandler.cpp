#include <Parallax/FS/POSIX/LocalFileHandler.hpp>

#include <Parallax/Platform.hpp>
#include <Parallax/FS/Path.hpp>

#if PARALLAX_PLATFORM_POSIX

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fstream>

namespace Parallax::FS
{
    LocalFileHandler::LocalFileHandler(std::shared_ptr<LocalFileSystem> fs, const std::string& path)
        : m_fs(fs)
        , m_path(path)
        , m_fileInfo(nullptr)
        , m_linkInfo(nullptr)
    {}

    LocalFileHandler::~LocalFileHandler()
    {
        if (m_fileInfo)
        {
            delete (struct stat*)m_fileInfo;
        }

        if (m_linkInfo)
        {
            delete (struct stat*)m_linkInfo;
        }
    }

    std::unique_ptr<FileHandler> LocalFileHandler::clone() const
    {
        return std::unique_ptr<FileHandler>(new LocalFileHandler(m_fs, m_path));
    }

    IFileSystem* LocalFileHandler::fs() const
    {
        return static_cast<IFileSystem*>(m_fs.get());
    }

    void LocalFileHandler::updateFileInfo()
    {
        if (m_fileInfo)
        {
            delete (struct stat*)m_fileInfo;
            m_fileInfo = nullptr;
        }

        if (m_linkInfo)
        {
            delete (struct stat*)m_linkInfo;
            m_linkInfo = nullptr;
        }
    }

    std::string LocalFileHandler::path() const
    {
        return m_path;
    }

    bool LocalFileHandler::exists()
    {
        readFileInfo();

        return (m_fileInfo != nullptr);
    }

    bool LocalFileHandler::isFile()
    {
        readFileInfo();

        if (m_fileInfo)
        {
            return S_ISREG(((struct stat*)m_fileInfo)->st_mode);
        }

        return false;
    }

    bool LocalFileHandler::isDirectory()
    {
        readFileInfo();

        if (m_fileInfo)
        {
            return S_ISDIR(((struct stat*)m_fileInfo)->st_mode);
        }

        return false;
    }

    bool LocalFileHandler::isSymbolicLink()
    {
        readLinkInfo();

        if (m_linkInfo)
        {
            return S_ISLNK(((struct stat*)m_linkInfo)->st_mode);
        }

        return false;
    }

    Collections::Vector<std::string> LocalFileHandler::listFiles() const
    {
        Collections::Vector<std::string> entries;

        DIR* dir = opendir(m_path.c_str());
        if (!dir)
        {
            return entries;
        }

        struct dirent* entry = readdir(dir);
        while (entry)
        {
            std::string name = entry->d_name;

            if (name != "." && name != "..")
            {
                entries.push_back(name);
            }

            entry = readdir(dir);
        }

        closedir(dir);

        return entries;
    }

    U32 LocalFileHandler::size()
    {
        readFileInfo();

        if (m_fileInfo)
        {
            if (S_ISREG(((struct stat*)m_fileInfo)->st_mode))
            {
                return ((struct stat*)m_fileInfo)->st_size;
            }
        }

        return 0;
    }

    U32 LocalFileHandler::lastAccessTime()
    {
        readFileInfo();

        if (m_fileInfo)
        {
            return ((struct stat*)m_fileInfo)->st_atime;
        }

        return 0;
    }

    U32 LocalFileHandler::lastModificationTime()
    {
        readFileInfo();

        if (m_fileInfo)
        {
            return ((struct stat*)m_fileInfo)->st_mtime;
        }

        return 0;
    }

    bool LocalFileHandler::createDirectory()
    {
        if (exists())
            return false;

        if (::mkdir(m_path.c_str(), 0755) != 0)
        {
            return false;
        }

        updateFileInfo();
        return true;
    }

    bool LocalFileHandler::removeDirectory()
    {
        if (!isDirectory())
            return false;

        if (::remove(m_path.c_str()) != 0)
        {
            return false;
        }

        updateFileInfo();
        return true;
    }

    bool LocalFileHandler::copy(FileHandler& dest)
    {
        if (!isFile())
            return false;

        std::string src = m_path;
        std::string dst = dest.path();

        if (dest.isDirectory())
        {
            std::string filename  = Path(m_path).filename();
            dst = Path(dest.path()).resolve(filename).fullPath();
        }

        std::ifstream in (src.c_str(), std::ios::binary);
        std::ofstream out(dst.c_str(), std::ios::binary);
        if (!in || !out)
        {
            return false;
        }

        out << in.rdbuf();

        return true;
    }

    bool LocalFileHandler::move(FileHandler& dest)
    {
        if (!exists())
            return false;

        std::string src = m_path;
        std::string dst = dest.path();

        if (dest.isDirectory())
        {
            std::string filename = Path(m_path).filename();
            dst = Path(dest.path()).resolve(filename).fullPath();
        }

        if (::rename(src.c_str(), dst.c_str()) != 0)
        {
            return false;
        }

        m_path = dst;
        updateFileInfo();

        return true;
    }

    bool LocalFileHandler::createLink(FileHandler& dest)
    {
        if (!exists())
            return false;

        std::string src = m_path;
        std::string dst = dest.path();

        if (dest.isDirectory())
        {
            std::string filename = Path(m_path).filename();
            dst = Path(dest.path()).resolve(filename).fullPath();
        }

        if (::link(src.c_str(), dst.c_str()) != 0)
        {
            return false;
        }

        return true;
    }

    bool LocalFileHandler::createSymbolicLink(FileHandler& dest)
    {
        if (!exists())
            return false;

        std::string src = m_path;
        std::string dst = dest.path();

        if (dest.isDirectory())
        {
            std::string filename = Path(m_path).filename();
            dst = Path(dest.path()).resolve(filename).fullPath();
        }

        if (::symlink(src.c_str(), dst.c_str()) != 0)
        {
            return false;
        }

        return true;
    }

    bool LocalFileHandler::rename(const std::string& filename)
    {
        if(!exists())
            return false;

        std::string path = Path(Path(m_path).directoryPath()).resolve(filename).fullPath();

        if (::rename(m_path.c_str(), path.c_str()) != 0)
        {
            return false;
        }

        m_path = path;
        updateFileInfo();

        return true;
    }

    bool LocalFileHandler::remove()
    {
        if (!isFile() && !isSymbolicLink())
            return false;

        if (::remove(m_path.c_str()) != 0)
        {
            return false;
        }

        updateFileInfo();
        return true;
    }

    std::unique_ptr<std::istream> LocalFileHandler::createInputStream(std::ios_base::openmode mode) const
    {
        return std::unique_ptr<std::istream>(new std::ifstream(m_path, mode));
    }

    std::unique_ptr<std::ostream> LocalFileHandler::createOutputStream(std::ios_base::openmode mode)
    {
        std::cout << "Path: " << m_path << std::endl;
        return std::unique_ptr<std::ostream>(new std::ofstream(m_path, mode));
    }

    void LocalFileHandler::readFileInfo()
    {
        if (m_fileInfo)
            return;

        m_fileInfo = (void*)new struct stat;

        if (stat(m_path.c_str(), (struct stat*)m_fileInfo) != 0)
        {
            delete (struct stat*)m_fileInfo;
            m_fileInfo = nullptr;
        }
    }

    void LocalFileHandler::readLinkInfo()
    {
        if (m_linkInfo)
            return;

        m_linkInfo = (void*)new struct stat;

        if (lstat(m_path.c_str(), (struct stat*)m_linkInfo) != 0)
        {
            delete (struct stat*)m_linkInfo;
            m_linkInfo = nullptr;
        }
    }
}

#endif