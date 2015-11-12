#ifdef LINUX_PLATFORM

#ifndef MPACK_LINUXCONSOLE_HPP
#define MPACK_LINUXCONSOLE_HPP

#include "Console.hpp"

namespace MPACK
{
        namespace Core
        {
                class LinuxConsole : public Console
                {
                public:
                        LinuxConsole();
                        virtual ~LinuxConsole();

                protected:
                        virtual void ClearImpl();

                        virtual void SetBGColorImpl(const BGColor color);
                        virtual void SetFGColorImpl(const FGColor color);
                        virtual void SetTitleImpl(const std::string str);
                        virtual void SetTitleImpl(const char str[]);
                        virtual void SetCursorPositionImpl(int x,int y);
                        virtual void ResetImpl();
                        
                        std::string m_FGColor;
                        std::string m_BGColor;
                };
        }
}

#endif

#endif
