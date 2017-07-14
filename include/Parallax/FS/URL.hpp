#ifndef PARALLAX_URL_HPP_GUARD
#define PARALLAX_URL_HPP_GUARD

#include <Parallax/Types.hpp>

#include <string>

namespace Parallax
{
    /**
     * \namespace   Parallax::FS
     * \ingroup     PIL
     */
    namespace FS
    {
        /**
         * \class   Url
         * \brief   Class to handle unified resource location
         *
         * \ingroup PIL
         */
        class Url
        {
        public:
            /**
             * \brief
             *  Constructor
             */
            Url();
            /**
             * \brief
             *  Copy-Constructor
             *
             * \param[in]   url Url to copy
             */
            Url(const Url& url);
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   url     URL
             */
            Url(const std::string& url);
            /**
             * \brief
             *  Constructor
             *
             * \param[in]   url     URL
             */
            Url(const char* url);

            /**
             * \brief
             *  Destructor
             */
            ~Url();

            /**
             * \brief
             *  Copy another url
             *
             * \param[in]   url URL to copy
             *
             * \return  New URL after copy
             */
            Url&                operator=(const Url& url);

            /**
             * \brief
             *  Get the stringify url
             *
             * \return  Whole URL
             */
            const std::string&  toString();
            /**
             * \brief
             *  Get the scheme
             *
             * \return  scheme
             */
            const std::string&  scheme();
            /**
             * \brief
             *  Get the location
             *
             * \return  location
             */
            const std::string&  location();
            /**
             * \brief
             *  Get the address
             *
             * \return  address
             */
            const std::string&  address();
            /**
             * \brief
             *  Get the host
             *
             * \return  host
             */
            const std::string&  host();
            /**
             * \brief
             *  Get the path
             *
             * \return  path
             */
            const std::string&  path();
            /**
             * \brief
             *  Get the query
             *
             * \return  query
             */
            const std::string&  query();
            /**
             * \brief
             *  Get the fragment
             *
             * \return  fragment
             */
            const std::string&  fragment();
            /**
             * \brief
             *  Get the login
             *
             * \return  login
             */
            const std::string&  login();
            /**
             * \brief
             *  Get the username
             *
             * \return  username
             */
            const std::string&  username();
            /**
             * \brief
             *  Get the password
             *
             * \return  password
             */
            const std::string&  password();

            /**
             * \brief
             *  Get the port
             *
             * \return  port
             */
            const U32           port();

        private:
            /**
             * \brief
             *  Analyze the url given
             */
            void                analyze();

        private:
            std::string     m_url;          /*!<    Whole URL                   */
            std::string     m_scheme;       /*!<    Scheme part of the URL      */
            std::string     m_location;     /*!<    Location part of the URL    */
            std::string     m_address;      /*!<    Address part of the URL     */
            std::string     m_host;         /*!<    Host part of the URL        */
            std::string     m_path;         /*!<    Path part of the URL        */
            std::string     m_query;        /*!<    Query part of the URL       */
            std::string     m_fragment;     /*!<    Fragment part of the URL    */
            std::string     m_login;        /*!<    Login part of the URL       */
            std::string     m_username;     /*!<    Username part of the URL    */
            std::string     m_password;     /*!<    Password part of the URL    */

            U32             m_port;         /*!<    Port of the URL             */

            bool            m_analyzed;     /*!<    Is the URL analyzed ?       */
        };
    }
}

#endif
