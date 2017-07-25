set (PARALLAX_HEADERS_ROOT ${ParallaxEngine_HEADER_DIR}/Parallax/)

set (PARALLAX_HEADERS
	${PARALLAX_HEADERS_ROOT}/Parallax.hpp
	${PARALLAX_HEADERS_ROOT}/Defines.hpp
	${PARALLAX_HEADERS_ROOT}/Macros.hpp
	${PARALLAX_HEADERS_ROOT}/Module.hpp
	${PARALLAX_HEADERS_ROOT}/Platform.hpp
	${PARALLAX_HEADERS_ROOT}/Strings.hpp
	${PARALLAX_HEADERS_ROOT}/Time.hpp
	${PARALLAX_HEADERS_ROOT}/Types.hpp

	${PARALLAX_HEADERS_ROOT}/Window.hpp

	${PARALLAX_HEADERS_ROOT}/Debug/Debug.hpp

	${PARALLAX_HEADERS_ROOT}/Collections/LinkedList.hpp
	${PARALLAX_HEADERS_ROOT}/Collections/LinkedList.inc
	${PARALLAX_HEADERS_ROOT}/Collections/Stack.hpp
	${PARALLAX_HEADERS_ROOT}/Collections/Stack.inc
	${PARALLAX_HEADERS_ROOT}/Collections/Vector.hpp
	${PARALLAX_HEADERS_ROOT}/Collections/Vector.inc

	${PARALLAX_HEADERS_ROOT}/FS/File.hpp
	${PARALLAX_HEADERS_ROOT}/FS/FileHandler.hpp
	${PARALLAX_HEADERS_ROOT}/FS/fs.hpp
	${PARALLAX_HEADERS_ROOT}/FS/IFileSystem.hpp
	${PARALLAX_HEADERS_ROOT}/FS/Path.hpp
	${PARALLAX_HEADERS_ROOT}/FS/URL.hpp

	${PARALLAX_HEADERS_ROOT}/FS/POSIX/LocalFileHandler.hpp
	${PARALLAX_HEADERS_ROOT}/FS/POSIX/LocalFileSystem.hpp

	${PARALLAX_HEADERS_ROOT}/Parsers/CSV/CSVParser.hpp
	${PARALLAX_HEADERS_ROOT}/Parsers/CSV/CSVRow.hpp
	${PARALLAX_HEADERS_ROOT}/Parsers/CSV/CSVRow.inc

	${PARALLAX_HEADERS_ROOT}/Renderers/Config.hpp
	${PARALLAX_HEADERS_ROOT}/Renderers/Defines.hpp
	${PARALLAX_HEADERS_ROOT}/Renderers/IRenderer.hpp
	${PARALLAX_HEADERS_ROOT}/Renderers/RendererGL.hpp
	${PARALLAX_HEADERS_ROOT}/Renderers/RendererVulkan.hpp

	${PARALLAX_HEADERS_ROOT}/Renderers/GLContexts/glx.hpp
	${PARALLAX_HEADERS_ROOT}/Renderers/GLContexts/wgl.hpp

	${PARALLAX_HEADERS_ROOT}/Threads/Task.hpp
	${PARALLAX_HEADERS_ROOT}/Threads/Task.inc
	${PARALLAX_HEADERS_ROOT}/Threads/ThreadManager.hpp
	${PARALLAX_HEADERS_ROOT}/Threads/ThreadPool.hpp
	${PARALLAX_HEADERS_ROOT}/Threads/ThreadPool.inc
	${PARALLAX_HEADERS_ROOT}/Threads/Worker.hpp
PARENT_SCOPE)