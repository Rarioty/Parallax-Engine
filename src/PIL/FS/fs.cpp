#include <Parallax/FS/fs.hpp>

#include <Parallax/FS/URL.hpp>
#include <Parallax/Platform.hpp>

#if PARALLAX_PLATFORM_WINDOWS
    #include <Parallax/FS/Windows/LocalFileSystem.hpp>
#else
    #include <Parallax/FS/POSIX/LocalFileSystem.hpp>
#endif

#include <memory>

namespace Parallax::FS
{
    File open(const std::string& path)
    {
        Url url(path);

        std::string localPath = url.path();

        static std::shared_ptr<LocalFileSystem> fs(new LocalFileSystem);

        return fs->open(localPath);
    }
}
