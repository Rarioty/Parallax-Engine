#ifndef FS_HPP
#define FS_HPP

#include <Parallax/fs/File.hpp>

namespace Parallax
{
    namespace fs
    {
        File open(const std::string& path);
    }
}

#endif
