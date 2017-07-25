#ifndef PARALLAX_FILE_SYSTEM_HPP_GUARD
#define PARALLAX_FILE_SYSTEM_HPP_GUARD

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
         * \class   AbstractFileSystem
         * \brief   Class to handle files
         *
         * \ingroup PIL
         */
        class IFileSystem
        {
        public:
            /**
             * \brief
             *  Destructor
             */
            virtual ~IFileSystem() = 0;

            /**
             * \brief
             *  Open a file with a specific path
             *
             * \param[in]   path    Path of the file to open
             *
             * \return  File
             */
            virtual File open(const std::string& path) = 0;
        };
    }
}

#endif
