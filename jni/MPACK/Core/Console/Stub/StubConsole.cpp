#include "StubConsole.hpp"

using namespace std;

namespace MPACK
{
        namespace Core
        {
                StubConsole::StubConsole()
                {
                }

                StubConsole::~StubConsole()
                {
                }

                void StubConsole::ClearImpl()
                {
                }

                void StubConsole::SetBGColorImpl(const BGColor color)
                {
                }

                void StubConsole::SetFGColorImpl(const FGColor color)
                {
                }

                void StubConsole::SetTitleImpl(const string str)
                {
                }

                void StubConsole::SetTitleImpl(const char str[])
                {
                }

                void StubConsole::SetCursorPositionImpl(int x,int y)
                {
                }

                void StubConsole::ResetImpl()
                {
                }
        }
}
