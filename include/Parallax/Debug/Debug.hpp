#ifndef PARALLAX_DEBUG_HPP_GUARD
#define PARALLAX_DEBUG_HPP_GUARD

#include <Parallax/Defines.hpp>
#include <Parallax/Types.hpp>
#include <cstdarg>

namespace Parallax
{
	namespace Debug
	{
		class IDebugger
		{
		public:
			virtual ~IDebugger() = 0;

			virtual void fatal(const char* message) = 0;
			virtual void traceVargs(const char* filepath, U16 line,
				const char* format, va_list argList) = 0;
		};

		bool Init();
		void SetNewDebugger(IDebugger* debugger);

		void Fatal(const char* format, ...);
		void Trace(const char* filePath, U16 line, const char* format, ...);

		void DebugBreak();
		void DebugOutput(const char* message);
		void DebugPrintfVargs(const char* format, va_list argList);
		void DebugPrintf(const char* format, ...);
		void DebugPrintfData(const void* data, U32 size, const char* format, ...);
	}
}

#define PARALLAX_TRACE(format, ...) \
        Parallax::Debug::Trace(__FILE__, U16(__LINE__), format "\n", ##__VA_ARGS__);

#define PARALLAX_WARN(condition, format, ...)				\
        if (!IGNORE_C4127(condition))						\
		{													\
            PARALLAX_TRACE("WARN " format, ##__VA_ARGS__);	\
		}

#define PARALLAX_CHECK(condition, format, ...)				\
        if (!IGNORE_C4127(condition))                       \
        {                                                   \
            PARALLAX_TRACE("CHECK " format, ##__VA_ARGS__); \
            Parallax::Fatal(format, ##__VA_ARGS__);         \
        }

#define PARALLAX_FATAL(condition, format, ...)					\
        if (!IGNORE_C4127(condition))							\
		{														\
            Parallax::Debug::Fatal(format "\n", ##__VA_ARGS__);		\
		}

#endif
