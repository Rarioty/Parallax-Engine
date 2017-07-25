#include <Parallax/FS/URL.hpp>

#include <iostream>

namespace Parallax::FS
{
    Url::Url()
        : m_url("")
        , m_scheme("")
        , m_location("")
        , m_address("")
        , m_host("")
        , m_path("")
        , m_query("")
        , m_fragment("")
        , m_login("")
        , m_username("")
        , m_password("")
        , m_port(0)
        , m_analyzed(false)
    {}

    Url::Url(const Url& url)
        : m_url(url.m_url)
        , m_scheme(url.m_scheme)
        , m_location(url.m_location)
        , m_address(url.m_address)
        , m_host(url.m_host)
        , m_path(url.m_path)
        , m_query(url.m_query)
        , m_fragment(url.m_fragment)
        , m_login(url.m_login)
        , m_username(url.m_username)
        , m_password(url.m_password)
        , m_port(url.m_port)
        , m_analyzed(url.m_analyzed)
    {}

    Url::Url(const std::string& url)
        : m_url(url)
        , m_scheme("")
        , m_location("")
        , m_address("")
        , m_host("")
        , m_path("")
        , m_query("")
        , m_fragment("")
        , m_login("")
        , m_username("")
        , m_password("")
        , m_port(0)
        , m_analyzed(false)
    {}

    Url::Url(const char* url)
        : m_url(url)
        , m_scheme("")
        , m_location("")
        , m_address("")
        , m_host("")
        , m_path("")
        , m_query("")
        , m_fragment("")
        , m_login("")
        , m_username("")
        , m_password("")
        , m_port(0)
        , m_analyzed(false)
    {}

    Url::~Url()
    {}

    Url& Url::operator=(const Url& url)
    {
        m_url       = url.m_url;
        m_scheme    = url.m_scheme;
        m_location  = url.m_location;
        m_address   = url.m_address;
        m_host      = url.m_host;
        m_path      = url.m_path;
        m_query     = url.m_query;
        m_fragment  = url.m_fragment;
        m_login     = url.m_login;
        m_username  = url.m_username;
        m_password  = url.m_password;
        m_port      = url.m_port;
        m_analyzed  = url.m_analyzed;

        return *this;
    }

    const std::string& Url::toString()
    {
        return m_url;
    }

    const std::string& Url::scheme()
    {
        analyze();
        return m_scheme;
    }

    const std::string& Url::location()
    {
        analyze();
        return m_location;
    }

    const std::string& Url::address()
    {
        analyze();
        return m_address;
    }

    const std::string& Url::host()
    {
        analyze();
        return m_host;
    }

    const std::string& Url::path()
    {
        analyze();
        return m_path;
    }

    const std::string& Url::query()
    {
        analyze();
        return m_query;
    }

    const std::string& Url::fragment()
    {
        analyze();
        return m_fragment;
    }

    const std::string& Url::login()
    {
        analyze();
        return m_login;
    }

    const std::string& Url::username()
    {
        analyze();
        return m_username;
    }

    const std::string& Url::password()
    {
        analyze();
        return m_password;
    }

    const U32 Url::port()
    {
        analyze();
        return m_port;
    }

    void Url::analyze()
    {
        if (m_analyzed)
            return;

        m_scheme    = "";
        m_location  = "";
        m_address   = "";
        m_host      = "";
        m_path      = "";
        m_query     = "";
        m_fragment  = "";
        m_login     = "";
        m_username  = "";
        m_password  = "";
        m_port      = 0;

        std::size_t pos = m_url.find("://");

        if (pos != std::string::npos)
        {
            m_scheme    = m_url.substr(0, pos + 3);
            m_location  = m_url.substr(pos + 3);
        }
        else
        {
            m_location = m_url;
        }

        pos = m_location.find("/");

        if (m_scheme != "" && m_scheme != "file://" && pos != std::string::npos)
        {
            m_address   = m_location.substr(0, pos);
            m_path      = m_location.substr(pos);
        }
        else
        {
            m_path      = m_location;
        }

        pos = m_address.find("@");

        if (pos != std::string::npos)
        {
            m_login = m_address.substr(0, pos);
            m_host  = m_address.substr(pos + 1);
        }
        else
        {
            m_login = "";
            m_host = m_address;
        }

        pos = m_login.find(":");

        if (pos != std::string::npos)
        {
            m_username = m_login.substr(0, pos);
            m_password = m_login.substr(pos + 1);
        }
        else
        {
            m_username = m_login;
        }

        pos = m_host.find(":");

        if (pos != std::string::npos)
        {
            m_port = (U32)strtoul(m_host.substr(pos + 1).c_str(), NULL, 0);
            m_host = m_host.substr(0, pos);
        }

        pos = m_path.find("?");

        if (pos != std::string::npos)
        {
            m_query = m_path.substr(pos + 1);
            m_path  = m_path.substr(0, pos);
        }

        pos = m_query.find("#");

        if (pos != std::string::npos)
        {
            m_fragment  = m_query.substr(pos + 1);
            m_query     = m_query.substr(0, pos);
        }

        m_analyzed = true;
    }
}
