#ifdef WINDOWS_PLATFORM

#include "WindowsConsole.hpp"

using namespace std;

namespace MPACK
{
        namespace Core
        {
                WindowsConsole::WindowsConsole()
                {
                }

                WindowsConsole::~WindowsConsole()
                {
                }

                void WindowsConsole::ClearImpl()
                {
                }

                void WindowsConsole::SetBGColorImpl(const BGColor color)
                {
                }

                void WindowsConsole::SetFGColorImpl(const FGColor color)
                {
                }

                void WindowsConsole::SetTitleImpl(const string str)
                {
                }

                void WindowsConsole::SetTitleImpl(const char str[])
                {
                }

                void WindowsConsole::SetCursorPositionImpl(int x,int y)
                {
                }

                void WindowsConsole::ResetImpl()
                {
                }
        }
}

#endif
