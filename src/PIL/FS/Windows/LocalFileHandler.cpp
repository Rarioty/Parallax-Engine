#include <Parallax/FS/Windows/LocalFileHandler.hpp>

#include <Parallax/Platform.hpp>
#include <Parallax/FS/Path.hpp>

#if PARALLAX_PLATFORM_WINDOWS

#include <Windows.h>
#include <fstream>

namespace Parallax::FS
{
	LocalFileHandler::LocalFileHandler(std::shared_ptr<LocalFileSystem> fs, const std::string& path)
		: m_fs(fs)
		, m_path(path)
		, m_fileInfo(nullptr)
	{}

	LocalFileHandler::~LocalFileHandler()
	{
		if (m_fileInfo)
		{
			delete (WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo;
		}
	}

	std::unique_ptr<FileHandler> LocalFileHandler::clone() const
	{
		return std::unique_ptr<FileHandler>(new LocalFileHandler(m_fs, m_path));
	}

	IFileSystem* LocalFileHandler::fs() const
	{
		return static_cast<IFileSystem*>(m_fs.get());
	}

	void LocalFileHandler::updateFileInfo()
	{
		if (m_fileInfo)
		{
			delete (WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo;
			m_fileInfo = nullptr;
		}
	}

	std::string LocalFileHandler::path() const
	{
		return m_path;
	}

	bool LocalFileHandler::exists()
	{
		readFileInfo();

		return (m_fileInfo != nullptr);
	}

	bool LocalFileHandler::isFile()
	{
		readFileInfo();

		if (m_fileInfo)
		{
			return (((WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo)->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
		}

		return false;
	}

	bool LocalFileHandler::isDirectory()
	{
		readFileInfo();

		if (m_fileInfo)
		{
			return (((WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo)->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
		}

		return false;
	}

	bool LocalFileHandler::isSymbolicLink()
	{
		readFileInfo();

		if (m_fileInfo)
		{
			return (((WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo)->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0;
		}

		return false;
	}

	Collections::Vector<std::string> LocalFileHandler::listFiles() const
	{
		Collections::Vector<std::string> entries;

		// Open directory
		WIN32_FIND_DATA findData;
		std::string query = Path(m_path).fullPath() + "/*";
		HANDLE findHandle = FindFirstFileA(query.c_str(), &findData);

		if (findHandle == INVALID_HANDLE_VALUE)
		{
			return entries;
		}

		// Read directory entries
		do
		{
			// Get name
			std::string name = findData.cFileName;

			// Ignore . and ..
			if (name != ".." && name != ".")
			{
				entries.push_back(name);
			}
		} while (FindNextFile(findHandle, &findData));

		// Close directory
		FindClose(findHandle);

		return entries;
	}

	U32 LocalFileHandler::size()
	{
		readFileInfo();

		if (m_fileInfo)
		{
			auto fileSizeH = ((WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo)->nFileSizeHigh;
			auto fileSizeL = ((WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo)->nFileSizeLow;

			return static_cast<U32>(static_cast<I64>(fileSizeH) << 32 | fileSizeL);
		}

		return 0;
	}

	U32 LocalFileHandler::lastAccessTime()
	{
		readFileInfo();

		if (m_fileInfo)
		{
			auto time = ((WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo)->ftLastAccessTime;

			return static_cast<U32>(static_cast<I64>(time.dwHighDateTime) << 32 | time.dwLowDateTime);
		}

		return 0;
	}

	U32 LocalFileHandler::lastModificationTime()
	{
		readFileInfo();

		if (m_fileInfo)
		{
			auto time = ((WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo)->ftLastWriteTime;

			return static_cast<U32>(static_cast<I64>(time.dwHighDateTime) << 32 | time.dwLowDateTime);
		}

		return 0;
	}

	bool LocalFileHandler::createDirectory()
	{
		if (exists())
			return false;

		if (!CreateDirectoryA(m_path.c_str(), nullptr))
		{
			return false;
		}

		updateFileInfo();
		return true;
	}

	bool LocalFileHandler::removeDirectory()
	{
		if (!isDirectory())
			return false;

		if (!RemoveDirectoryA(m_path.c_str()))
		{
			return false;
		}

		updateFileInfo();
		return true;
	}

	bool LocalFileHandler::copy(FileHandler& dest)
	{
		if (!isFile())
			return false;

		std::string src = m_path;
		std::string dst = dest.path();

		if (dest.isDirectory())
		{
			std::string filename = Path(m_path).filename();
			dst = Path(dest.path()).resolve(filename).fullPath();
		}

		if (!CopyFileA(src.c_str(), dst.c_str(), FALSE))
		{
			return false;
		}

		updateFileInfo();
		return true;
	}

	bool LocalFileHandler::move(FileHandler& dest)
	{
		if (!exists())
			return false;

		std::string src = m_path;
		std::string dst = dest.path();

		if (dest.isDirectory())
		{
			std::string filename = Path(m_path).filename();
			dst = Path(dest.path()).resolve(filename).fullPath();
		}

		if (!MoveFileA(src.c_str(), dst.c_str()))
		{
			return false;
		}

		m_path = dst;
		updateFileInfo();

		return true;
	}

	bool LocalFileHandler::createLink(FileHandler& dest)
	{
		if (!exists())
			return false;

		std::string src = m_path;
		std::string dst = dest.path();

		if (dest.isDirectory())
		{
			std::string filename = Path(m_path).filename();
			dst = Path(dest.path()).resolve(filename).fullPath();
		}

		if (!CreateHardLinkA(src.c_str(), dst.c_str(), 0))
		{
			return false;
		}

		return true;
	}

	bool LocalFileHandler::createSymbolicLink(FileHandler& dest)
	{
		if (!exists())
			return false;

		std::string src = m_path;
		std::string dst = dest.path();

		if (dest.isDirectory())
		{
			std::string filename = Path(m_path).filename();
			dst = Path(dest.path()).resolve(filename).fullPath();
		}

		if (!CreateSymbolicLinkA(src.c_str(), dst.c_str(), 0))
		{
			return false;
		}

		return true;
	}

	bool LocalFileHandler::rename(const std::string& filename)
	{
		if (!exists())
			return false;

		std::string path = Path(Path(m_path).directoryPath()).resolve(filename).fullPath();

		if (!MoveFileA(m_path.c_str(), path.c_str()))
		{
			return false;
		}

		m_path = path;
		updateFileInfo();

		return true;
	}

	bool LocalFileHandler::remove()
	{
		if (!isFile() && !isSymbolicLink())
			return false;

		if (!DeleteFileA(m_path.c_str()))
		{
			return false;
		}

		updateFileInfo();
		return true;
	}

	std::unique_ptr<std::istream> LocalFileHandler::createInputStream(std::ios_base::openmode mode) const
	{
		return std::unique_ptr<std::istream>(new std::ifstream(m_path, mode));
	}

	std::unique_ptr<std::ostream> LocalFileHandler::createOutputStream(std::ios_base::openmode mode)
	{
		std::cout << "Path: " << m_path << std::endl;
		return std::unique_ptr<std::ostream>(new std::ofstream(m_path, mode));
	}

	void LocalFileHandler::readFileInfo()
	{
		if (m_fileInfo)
			return;

		m_fileInfo = (void*)new WIN32_FILE_ATTRIBUTE_DATA;

		if (!GetFileAttributesExA(m_path.c_str(), GetFileExInfoStandard, (WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo))
		{
			delete (WIN32_FILE_ATTRIBUTE_DATA*)m_fileInfo;
			m_fileInfo = nullptr;
		}
	}
}

#endif