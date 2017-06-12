#include <PIL/File.hpp>

namespace Parallax
{
    File::File(std::string filepath, File::openmode mode)
        : m_filepath(filepath)
        , m_openmode(mode)
        , m_stream(nullptr)
    {}

    std::string File::getFilepath() const
    {
        return m_filepath;
    }

    File::openmode File::getOpenmode() const
    {
        return m_openmode;
    }

    int File::open()
    {
        std::ios_base::openmode mode;
        int error_code = 0;

        // Check if operation will fail or not
        if (this->m_openmode & File::openmode::TRUNC && this->m_openmode & File::openmode::APP)
            error_code = -1;

        if (this->m_openmode & File::openmode::TRUNC && !(this->m_openmode & File::openmode::OUT))
            error_code -1;

        // Generate standard c++ mode
        if (error_code == 0)
        {
            if (this->m_openmode & File::openmode::IN)
                mode |= std::ios_base::in;
            if (this->m_openmode & File::openmode::OUT)
                mode |= std::ios_base::out;
            if (this->m_openmode & File::openmode::BINARY)
                mode |= std::ios_base::binary;
            if (this->m_openmode & File::openmode::ATE)
                mode |= std::ios_base::ate;
            if (this->m_openmode & File::openmode::APP)
                mode |= std::ios_base::app;
            if (this->m_openmode & File::openmode::TRUNC)
                mode |= std::ios_base::trunc;

            // Instanciate a stream
            m_stream = new std::fstream(this->m_filepath, mode);

            if (m_stream)
            {
                // Open it
                m_stream->open(this->m_filepath);

                if (!m_stream->is_open())
                    error_code = -1;
            }
            else
                error_code = -1;
        }

        return error_code;
    }

    int File::close()
    {
        int error_code = 0;

        // If the stream is open, close it
        if (m_stream->is_open())
            m_stream->close();
        else
            error_code = -1;

        return error_code;
    }
}
