#include <Parallax/FS/File.hpp>

#include <Parallax/FS/FileHandler.hpp>
#include <Parallax/FS/Path.hpp>

#include <array>

#ifdef PARALLAX_BUILD_SYSTEM_APPLE
    #define COMMON_DIGEST_FOR_OPENSSL
    #include <CommonCrypto/CommonDigest.h>
    #define SHA1 CC_SHA1
#else
    #include <openssl/sha.h>
#endif

namespace Parallax::FS
{
    File::File()
        : m_handler(nullptr)
    {}

    File::File(std::unique_ptr<FileHandler>&& handler)
        : m_handler(std::move(handler))
    {}

    File::File(const File& file)
        : m_handler(file.m_handler ? file.m_handler->clone() : nullptr)
    {}

    File::~File()
    {}

    File& File::operator=(const File& file)
    {
        if (file.m_handler)
        {
            m_handler = file.m_handler->clone();
        }
        else
        {
            m_handler.reset(nullptr);
        }

        return *this;
    }

    std::string File::path() const
    {
        return m_handler ? m_handler->path() : "";
    }

    std::string File::filename() const
    {
        return m_handler ? m_handler->path() : "";
    }

    void File::updateFileInfo()
    {
        if (m_handler)
            m_handler->updateFileInfo();
    }

    bool File::exists() const
    {
        return m_handler ? m_handler->exists() : false;
    }

    bool File::isFile() const
    {
        return m_handler ? m_handler->isFile() : false;
    }

    bool File::isDirectory() const
    {
        return m_handler ? m_handler->isDirectory() : false;
    }

    bool File::isSymbolicLink() const
    {
        return m_handler ? m_handler->isSymbolicLink() : false;
    }

    Collections::Vector<std::string> File::listFiles() const
    {
        return m_handler ? m_handler->listFiles() : Collections::Vector<std::string>();
    }

    U32 File::size() const
    {
        return m_handler ? m_handler->size() : 0;
    }

    U32 File::lastAccessTime() const
    {
        return m_handler ? m_handler->lastAccessTime() : 0;
    }

    U32 File::lastModificationTime() const
    {
        return m_handler ? m_handler->lastModificationTime() : 0;
    }

    std::string File::sha1() const
    {
        if (!isFile())
        {
            return "";
        }

        auto inputStream = createInputStream();
        if (!inputStream)
        {
            return "";
        }

        unsigned char hash[20];
        SHA_CTX context;
        SHA1_Init(&context);

        while (!inputStream->eof())
        {
            std::array<char, 1024> buf;
            inputStream->read(buf.data(), buf.size());

            size_t count = inputStream->gcount();
            if (count > 0)
            {
                SHA1_Update(&context, buf.data(), count);
            } else break;
        }

        SHA1_Final(hash, &context);

        return std::string(reinterpret_cast<char*>(hash));
    }

    File File::parentDirectory()
    {
        return m_handler ? m_handler->fs()->open(Path(m_handler->path()).resolve("..").resolved()) : File();
    }

    File File::open(const std::string& path)
    {
        return m_handler ? m_handler->fs()->open(Path(m_handler->path()).resolve(path).fullPath()) : File();
    }

    bool File::createDirectory()
    {
        if (!m_handler)
        {
            return false;
        }

        return m_handler->createDirectory();
    }

    bool File::removeDirectory()
    {
        if (!m_handler)
        {
            return false;
        }

        return m_handler->removeDirectory();
    }

    void File::copyDirectoryRec(File& dst)
    {
        // TODO
    }

    void File::removeDirectoryRec()
    {
        // TODO
    }

    bool File::copy(File& dst)
    {
        if (!m_handler)
            return false;

        if (m_handler->fs() == dst.m_handler->fs())
        {
            bool result = m_handler->copy(*dst.m_handler.get());

            return result;
        }
        else
        {
            return genericCopy(dst);
        }
    }

    bool File::move(File& dst)
    {
        if (!m_handler)
            return false;

        if (m_handler->fs() == dst.m_handler->fs())
        {
            bool result = m_handler->move(*dst.m_handler.get());

            return result;
        }
        else
        {
            return genericMove(dst);
        }
    }

    bool File::createLink(File& dst)
    {
        if (!m_handler)
            return false;

        if (m_handler->fs() == dst.m_handler->fs())
        {
            bool result = m_handler->createLink(*dst.m_handler.get());

            return result;
        }
        else
        {
            return false;
        }
    }

    bool File::createSymbolicLink(File& dst)
    {
        if (!m_handler)
            return false;

        if (m_handler->fs() == dst.m_handler->fs())
        {
            bool result = m_handler->createSymbolicLink(*dst.m_handler.get());

            return result;
        }
        else
        {
            return false;
        }
    }

    bool File::rename(const std::string& filename)
    {
        if (!m_handler)
            return false;

        return m_handler->rename(filename);
    }

    bool File::remove()
    {
        if (!m_handler)
            return false;

        return m_handler->remove();
    }

    std::unique_ptr<std::istream> File::createInputStream(std::ios_base::openmode mode) const
    {
        if (!m_handler)
            return nullptr;

        return m_handler->createInputStream(mode);
    }

    std::unique_ptr<std::ostream> File::createOutputStream(std::ios_base::openmode mode)
    {
        if (!m_handler)
            return nullptr;

        return m_handler->createOutputStream(mode);
    }

    std::string File::readFile() const
    {
        if (isFile())
        {
            auto inputStream = createInputStream();
            if (!inputStream)
                return "";

            std::stringstream buffer;
            buffer << inputStream->rdbuf();

            return buffer.str();
        }

        return "";
    }

    bool File::writeFile(const std::string& content)
    {
        auto outputStream = createOutputStream();
        if (!outputStream)
            return false;

        (*outputStream) << content;

        return true;
    }

    bool File::genericCopy(File& dst)
    {
        if (!m_handler)
            return false;

        auto in = createInputStream(std::ios::binary);
        auto out = dst.createOutputStream(std::ios::binary | std::ios::trunc);

        if (!in || !out)
        {
            return false;
        }

        (*out) << in->rdbuf();
        out->flush();

        return true;
    }

    bool File::genericMove(File& dst)
    {
        if (!genericCopy(dst))
            return false;

        return remove();
    }
}
