#ifdef ANDROID_PLATFORM

#ifndef MPACK_ANDROIDCONSOLE_HPP
#define MPACK_ANDROIDCONSOLE_HPP

#include "Console.hpp"

namespace MPACK
{
        namespace Core
        {
                class AndroidConsole : public Console
                {
                public:
                        AndroidConsole();
                        virtual ~AndroidConsole();

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
