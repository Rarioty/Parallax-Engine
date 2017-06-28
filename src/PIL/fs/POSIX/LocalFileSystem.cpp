#include <PIL/fs/POSIX/LocalFileSystem.hpp>

#include <PIL/fs/POSIX/LocalFileHandler.hpp>

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
