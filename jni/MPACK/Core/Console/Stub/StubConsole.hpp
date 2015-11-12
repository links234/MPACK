#ifndef MPACK_STUBCONSOLE_HPP
#define MPACK_STUBCONSOLE_HPP

#include "Console.hpp"

namespace MPACK
{
        namespace Core
        {
                class StubConsole : public Console
                {
                public:
                        StubConsole();
                        virtual ~StubConsole();
                        
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
