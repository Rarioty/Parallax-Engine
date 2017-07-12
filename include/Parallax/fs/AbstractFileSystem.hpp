#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include <Parallax/fs/File.hpp>

namespace Parallax
{
    namespace fs
    {
        class AbstractFileSystem
        {
        public:
            AbstractFileSystem(){}
            ~AbstractFileSystem(){}

            virtual File open(const std::string& path) = 0;
        };
    }
}

#endif
