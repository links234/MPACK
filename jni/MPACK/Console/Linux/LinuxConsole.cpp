#ifdef LINUX_PLATFORM

#include "LinuxConsole.hpp"

using namespace std;

namespace MPACK
{
        namespace Core
        {
                LinuxConsole::LinuxConsole()
                {
                }

                LinuxConsole::~LinuxConsole()
                {
                }

                void LinuxConsole::ClearImpl()
                {
                }

                void LinuxConsole::SetBGColorImpl(const BGColor color)
                {
                }

                void LinuxConsole::SetFGColorImpl(const FGColor color)
                {
                }

                void LinuxConsole::SetTitleImpl(const string str)
                {
                }

                void LinuxConsole::SetTitleImpl(const char str[])
                {
                }

                void LinuxConsole::SetCursorPositionImpl(int x,int y)
                {
                }
        }
}

#endif
