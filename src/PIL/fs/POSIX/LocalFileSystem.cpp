#include <Parallax/fs/POSIX/LocalFileSystem.hpp>

#include <Parallax/fs/POSIX/LocalFileHandler.hpp>

namespace Parallax::fs
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
