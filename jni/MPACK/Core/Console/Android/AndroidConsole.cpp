#ifdef ANDROID_PLATFORM

#include "AndroidConsole.hpp"

using namespace std;

namespace MPACK
{
        namespace Core
        {
                AndroidConsole::AndroidConsole()
                {
                }

                AndroidConsole::~AndroidConsole()
                {
                }

                void AndroidConsole::ClearImpl()
                {
                }

                void AndroidConsole::SetBGColorImpl(const BGColor color)
                {
                }

                void AndroidConsole::SetFGColorImpl(const FGColor color)
                {
                }

                void AndroidConsole::SetTitleImpl(const string str)
                {
                }

                void AndroidConsole::SetTitleImpl(const char str[])
                {
                }

                void AndroidConsole::SetCursorPositionImpl(int x,int y)
                {
                }

                void AndroidConsole::ResetImpl()
                {
                }
        }
}

#endif
