#ifndef PARALLAX_FS_HPP_GUARD
#define PARALLAX_FS_HPP_GUARD

#include <Parallax/FS/File.hpp>

namespace Parallax
{
    /**
     * \namespace   Parallax::FS
     * \ingroup     PIL
     */
    namespace FS
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
