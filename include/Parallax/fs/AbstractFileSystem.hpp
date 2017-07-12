#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

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
         * \class   AbstractFileSystem
         * \brief   Class to handle files
         *
         * \ingroup PIL
         */
        class AbstractFileSystem
        {
        public:
            /**
             * \brief
             *  Constructor
             */
            AbstractFileSystem(){}
            /**
             * \brief
             *  Destructor
             */
            ~AbstractFileSystem(){}

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
