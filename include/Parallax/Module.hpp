#ifndef MODULE_HPP
#define MODULE_HPP

namespace Parallax
{
    /**
     * \namespace   Parallax::Core
     * \ingroup     Core
     */
    namespace Core
    {
        /**
         * \class   Module
         * \brief   Module class for subsystem start and stop
         *
         * \ingroup Core
         */
        class Module
        {
        public:
            /**
             * \brief
             *  Constructor
             */
            Module(){}
            /**
             * \brief
             *  Destructor
             */
            ~Module(){}

            /**
             * \brief
             *  Initialize the subsystem
             */
            virtual void Init() = 0;
            /**
             * \brief
             *  Stop the subsystem
             */
            virtual void Shutdown() = 0;
        };
    }
}

#endif
