#ifndef MPACK_LOG_HPP
#define MPACK_LOG_HPP

namespace MPACK
{
	namespace Core
	{
		class Log
		{
		public:
			static void Initialize();
			static void Destroy();

			static void Error(const char* pMessage, ...);
			static void Warn(const char* pMessage, ...);
			static void Info(const char* pMessage, ...);
			static void Debug(const char* pMessage, ...);
		};
	}
}

#endif
