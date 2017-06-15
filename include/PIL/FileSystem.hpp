#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include <boost/filesystem.hpp>

/**
 * The filesystem must allow to:
 *  - Manipulate file names and paths
 *  - Open, close, read and write individual files
 *  - Scan the content of a directory
 */

namespace Parallax
{
    /*
     * For now on, use Boost for FileSystem until we have to optimize the code or the compilation don't work
     */
    /**
     * \namespace   Parallax::FileSystem
     * \ingroup     PIL
     */
    namespace FileSystem = boost::filesystem;
}

#endif
