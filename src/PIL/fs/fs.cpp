#include <Parallax/fs/fs.hpp>

#include <Parallax/fs/URL.hpp>
#include <Parallax/Parallax.hpp>

#ifdef PARALLAX_BUILD_SYSTEM_WIN32
    #include <Parallax/fs/Windows/LocalFileSystem.hpp>
#else
    #include <Parallax/fs/POSIX/LocalFileSystem.hpp>
#endif

#include <memory>

namespace Parallax::fs
{
    File open(const std::string& path)
    {
        Url url(path);

        std::string localPath = url.path();

        static std::shared_ptr<LocalFileSystem> fs(new LocalFileSystem);

        return fs->open(localPath);
    }
}
