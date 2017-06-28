#include <PIL/fs/fs.hpp>


#ifdef PARALLAX_BUILD_SYSTEM_WIN32
    #include <PIL/fs/Windows/LocalFileSystem.hpp>
#else
    #include <PIL/fs/POSIX/LocalFileSystem.hpp>
#endif

#include <PIL/fs/URL.hpp>
#include <Parallax.hpp>

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
