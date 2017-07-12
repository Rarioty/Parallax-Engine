#ifndef URL_HPP
#define URL_HPP

#include <Parallax/Types.hpp>

#include <string>

namespace Parallax
{
    namespace fs
    {
        class Url
        {
        public:
            Url();
            Url(const Url& url);
            Url(const std::string& url);
            Url(const char* url);

            ~Url();

            Url&                operator=(const Url& url);

            const std::string&  toString();
            const std::string&  scheme();
            const std::string&  location();
            const std::string&  address();
            const std::string&  host();
            const std::string&  path();
            const std::string&  query();
            const std::string&  fragment();
            const std::string&  login();
            const std::string&  username();
            const std::string&  password();

            const U32           port();

        private:
            void                analyze();

        private:
            std::string     m_url;
            std::string     m_scheme;
            std::string     m_location;
            std::string     m_address;
            std::string     m_host;
            std::string     m_path;
            std::string     m_query;
            std::string     m_fragment;
            std::string     m_login;
            std::string     m_username;
            std::string     m_password;

            U32             m_port;

            bool            m_analyzed;
        };
    }
}

#endif
