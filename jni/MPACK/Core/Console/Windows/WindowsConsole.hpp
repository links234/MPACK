#ifdef WINDOWS_PLATFORM

#ifndef MPACK_WINDOWSCONSOLE_HPP
#define MPACK_WINDOWSCONSOLE_HPP

#include "Console.hpp"

namespace MPACK
{
        namespace Core
        {
                class WindowsConsole : public Console
                {
                public:
                        WindowsConsole();
                        virtual ~WindowsConsole();

                protected:
                        virtual void ClearImpl();

                        virtual void SetBGColorImpl(const BGColor color);
                        virtual void SetFGColorImpl(const FGColor color);
                        virtual void SetTitleImpl(const std::string str);
                        virtual void SetTitleImpl(const char str[]);
                        virtual void SetCursorPositionImpl(int x,int y);
                        virtual void ResetImpl();
                };
        }
}

#endif

#endif
