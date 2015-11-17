#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "FileLogger.hpp"

#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <ctime>

#define	BUFFER_SIZE 	64*1024
#define TBUFFER_SIZE	128
#define BASESIZE		3

namespace MPACK
{
	namespace Core
	{
		FileLogger::FileLogger(std::string fileName)
			: m_bDatePrinting(true), m_iBaseSize(BASESIZE), m_bClear(false), m_bIsActive(true), m_sFileName(fileName)
		{
			Clear();
			Init();
		}

		FileLogger::FileLogger(const char *fileName)
			: m_bDatePrinting(true), m_iBaseSize(BASESIZE), m_bClear(false), m_bIsActive(true), m_sFileName(fileName)
		{
			Clear();
			Init();
		}

		FileLogger::~FileLogger()
		{
			if(m_bClear)
			{
				Clear();
			}
			else
			{
				time_t t;
				time(&t);
				tm *t_tm;
				t_tm=localtime(&t);
				char buffer[256];
				memset(buffer,0,256);
				strftime(buffer,256,"%X - %d/%m/%y",t_tm);
				m_hLog=fopen(m_sFileName.c_str(),"at");
				if(!m_hLog)
				{
					Disable();
				}
				if(m_bDatePrinting)
				{
					fprintf(m_hLog,"</pre>\n");
				}
				fprintf(m_hLog,"<pre><font color=GREEN face=\"Arial\" size=%d>\nLog ended at %s</font></pre>\n</body>\n</html>\n",m_iBaseSize+1,buffer);
				fclose(m_hLog);
			}
		}

		void FileLogger::Print(MessageType messageType, std::string message)
		{
			if(!m_bIsActive)
			{
				return;
			}

			time_t t;
			time(&t);
			tm *t_tm;
			t_tm=localtime(&t);

			char tbuffer[TBUFFER_SIZE];
			memset(tbuffer,0,TBUFFER_SIZE);
			strftime(tbuffer,TBUFFER_SIZE,"%A %d/%m/%y at %X",t_tm);

			m_hLog=fopen(m_sFileName.c_str(),"at");
			if(!m_hLog)
			{
				Disable();
			}
			if(m_bDatePrinting)
			{
				//fprintf(m_hLog,"\n<pre>\n<font color=%s size=\"%d\" face=\"%s\"><b>%s:</b></font>",GetColor(messageType),m_iBaseSize+GetSize(messageType)+1,GetFace(messageType),tbuffer);
				//fprintf(m_hLog,"<font color=%s size=\"%d\" face=\"%s\">%s</font>\n</pre>\n",GetColor(messageType),m_iBaseSize+GetSize(messageType),GetFace(messageType),message.c_str());
			}
			else
			{
				//fprintf(m_hLog,"<font color=%s size=\"%d\" face=\"%s\">%s</font>\n",GetColor(messageType),m_iBaseSize+GetSize(messageType),GetFace(messageType),message.c_str());
			}
			fclose(m_hLog);
		}

		void FileLogger::Print(MessageType messageType, const char *message, ...)
		{
			if(!m_bIsActive)
			{
				return;
			}

			time_t t;
			time(&t);
			tm *t_tm;
			t_tm=localtime(&t);

			char tbuffer[TBUFFER_SIZE];
			memset(tbuffer,0,TBUFFER_SIZE);
			strftime(tbuffer,TBUFFER_SIZE,"%A %d/%m/%y at %X",t_tm);

			char buffer[BUFFER_SIZE];
			memset(buffer,0,BUFFER_SIZE);

			va_list args;
			va_start(args,message);
			vsprintf(buffer,message,args);
			va_end(args);



			m_hLog=fopen(m_sFileName.c_str(),"at");
			if(!m_hLog)
			{
				Disable();
			}
			if(m_bDatePrinting)
			{
				fprintf(m_hLog,"\n<pre>\n<font color=%s size=\"%d\" face=\"%s\"><b>%s:</b></font>",GetColor(messageType),m_iBaseSize+GetSize(messageType)+1,GetFace(messageType),tbuffer);
				fprintf(m_hLog,"<font color=%s size=\"%d\" face=\"%s\">%s</font>\n</pre>\n",GetColor(messageType),m_iBaseSize+GetSize(messageType),GetFace(messageType),buffer);
			}
			else
			{
				fprintf(m_hLog,"<font color=%s size=\"%d\" face=\"%s\">%s</font>\n",GetColor(messageType),m_iBaseSize+GetSize(messageType),GetFace(messageType),buffer);
			}
			fclose(m_hLog);
		}

		const char* FileLogger::GetColor(MessageType messageType)
		{
			switch(messageType)
			{
				case Succes:
					return "GREEN";
				case Failure:
					return "GRAY";
				case CriticalFailure:
					return "RED";
				case Information:
					return "BLUE";
				case Warning:
					return "YELLOW";
			}
			return "WHITE";
		}

		const char* FileLogger::GetFace(MessageType messageType)
		{
			switch(messageType)
			{
				case Succes:
					return "Arial";
				case Failure:
					return "Arial";
				case CriticalFailure:
					return "Arial";
				case Information:
					return "Arial";
				case Warning:
					return "Arial";
			}
			return "Arial";
		}

		int FileLogger::GetSize(MessageType messageType)
		{
			switch(messageType)
			{
				case Succes:
					return 0;
				case Failure:
					return 0;
				case CriticalFailure:
					return 0;
				case Information:
					return 0;
				case Warning:
					return 0;
			}
			return 0;
		}

		void FileLogger::Init()
		{
			time_t t;
			time(&t);
			tm *t_tm;
			t_tm=localtime(&t);
			char buffer[256];
			memset(buffer,0,256);
			strftime(buffer,256,"%d/%m/%y",t_tm);
			m_hLog=fopen(m_sFileName.c_str(),"at");
			fprintf(m_hLog,"<html>\n<head>\n<title>%s</title>\n<head>\n\n<body bgcolor=BLACK>\n",buffer);

			memset(buffer,0,256);
			strftime(buffer,256,"%X - %d/%m/%y",t_tm);
			fprintf(m_hLog,"<pre><font color=GREEN face=\"Arial\" size=%d>Log started at %s\n\n</font></pre>\n\n",m_iBaseSize+1,buffer);
			fclose(m_hLog);
		}

		int FileLogger::GetTextSize()
		{
			return m_iBaseSize;
		}

		void FileLogger::EnableDatePrinting()
		{
			if(!m_bDatePrinting)
			{
				m_hLog=fopen(m_sFileName.c_str(),"at");
				fprintf(m_hLog,"</pre>\n");
				fclose(m_hLog);
			}
			m_bDatePrinting=true;
		}

		void FileLogger::DisableDatePrinting()
		{
			if(m_bDatePrinting)
			{
				m_hLog=fopen(m_sFileName.c_str(),"at");
				fprintf(m_hLog,"<pre>");
				fclose(m_hLog);
			}
			m_bDatePrinting=false;
		}

		bool FileLogger::ClearEnabled()
		{
			return m_bClear;
		}

		bool FileLogger::ClearDisabled()
		{
			return !m_bClear;
		}

		void FileLogger::EnableClear()
		{
			m_bClear=true;
		}

		void FileLogger::DisableClear()
		{
			m_bClear=false;
		}

		void FileLogger::Clear()
		{
			remove(m_sFileName.c_str());
		}

		void FileLogger::Enable()
		{
			m_bIsActive = true;
		}

		void FileLogger::Disable()
		{
			m_bIsActive = false;
		}

		bool FileLogger::Enabled()
		{
			return m_bIsActive;
		}

		bool FileLogger::Disabled()
		{
			return !m_bIsActive;
		}
	}
}

#endif
