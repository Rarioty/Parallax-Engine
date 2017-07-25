#include <Parallax/FS/POSIX/LocalFileSystem.hpp>

#include <Parallax/Platform.hpp>

#if PARALLAX_PLATFORM_POSIX

#include <Parallax/FS/POSIX/LocalFileHandler.hpp>

namespace Parallax::FS
{
    LocalFileSystem::LocalFileSystem()
    {}

    LocalFileSystem::~LocalFileSystem()
    {}

    File LocalFileSystem::open(const std::string& path)
    {
        return File(
            std::unique_ptr<FileHandler>(
                new LocalFileHandler(shared_from_this(), path)
            )
        );
    }
}

#endif