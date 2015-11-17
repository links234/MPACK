#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_FILELOGGER_H
#define MPACK_FILELOGGER_H

#include <string>

#define ERROR_CODE_LOGGER_FAIL 0

namespace MPACK
{
	namespace Core
	{
		class FileLogger
		{
		public:
			FileLogger(std::string fileName);
			FileLogger(const char *fileName);

			enum MessageType
			{
				Succes = 0,
				Failure,
				CriticalFailure,
				Information,
				Warning
			};

			void Print(MessageType messageType, std::string message);
			void Print(MessageType messageType, const char *message, ...);
			void Clear();
			void Enable();
			void Disable();
			void EnableClear();
			void DisableClear();
			void EnableDatePrinting();
			void DisableDatePrinting();

			int GetTextSize();

			bool Enabled();
			bool Disabled();
			bool ClearEnabled();
			bool ClearDisabled();

			~FileLogger();
		private:
			void Init();

			int GetSize(MessageType messageType);

			const char* GetColor(MessageType messageType);
			const char* GetFace(MessageType messageType);

			int m_iBaseSize;
			bool m_bIsActive;
			bool m_bClear;
			bool m_bDatePrinting;
			std::string m_sFileName;
			FILE *m_hLog;
		};
	}
}

#endif

#endif
