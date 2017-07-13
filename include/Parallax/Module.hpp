#ifndef MODULE_HPP
#define MODULE_HPP

namespace Parallax
{
    /**
     * \class   Module
     * \brief   Module class for subsystem start and stop
     */
    class Module
    {
    public:
        enum State
        {
            INITIALIZING,
            INITIALIZED,
            SHUTDOWN
        };
        
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
        virtual bool Init() = 0;
        /**
         * \brief
         *  Stop the subsystem
         */
        virtual void Shutdown() = 0;

    protected:
        State   m_state;    /*!<    Current state of module     */
    };
}

#endif
