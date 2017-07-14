#ifndef PARALLAX_FS_HPP_GUARD
#define PARALLAX_FS_HPP_GUARD

#include <Parallax/fs/File.hpp>

namespace Parallax
{
    /**
     * \namespace   Parallax::fs
     * \ingroup     PIL
     */
    namespace fs
    {
        /**
         * \brief
         *  Open a file with a specific path
         *
         * \param[in]   Path    Path to the file to open
         *
         * \return  File
         */
        File open(const std::string& path);
    }
}

#endif
