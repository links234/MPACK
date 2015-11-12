#include "Console.hpp"

#include <iostream>

#include "AndroidConsole.hpp"
#include "LinuxConsole.hpp"
#include "WindowsConsole.hpp"

using namespace std;

namespace MPACK
{
        namespace Core
        {
                Console *Console::s_pConsole = NULL;

                void Console::Write(string str)
                {
                        cout << str;
                }

                void Console::Write(int v)
                {
                        cout << v;
                }

                void Console::Write(bool v)
                {
                        cout << (v ? "True" : "False");
                }

                void Console::Write(char str[])
                {
                        cout << str;
                }

                void Console::Write(char c)
                {
                        cout << c;
                }

                void Console::Write(double d)
                {
                        cout << d;
                }

                void Console::Write(float f)
                {
                        cout << f;
                }

                void Console::WriteLine(string str)
                {
                        cout << str << endl;
                }

                void Console::WriteLine()
                {
                        cout << endl;
                }

                void Console::WriteLine(char str[])
                {
                        cout << str << endl;
                }

                char Console::ReadKey()
                {
                        return getchar();
                }

                string Console::ReadLine()
                {
                        string str;
                        char c = getchar();
                        while (c != '\n')
                        {
                                if(c == '\r')
                                {
                                        continue;
                                }
                                else
                                {
                                        str += c;
                                }
                                c = getchar();
                        }
                        return str;
                }

                void Console::Cleanup()
                {
                        if (s_pConsole)
                        {
                                delete s_pConsole;
                                s_pConsole = NULL;
                        }
                }

                void Console::Clear()
                {
                        GetConsole()->ClearImpl();
                }

                void Console::SetBGColor(const BGColor color)
                {
                        GetConsole()->SetBGColorImpl(color);
                }

                void Console::SetFGColor(const FGColor color)
                {
                        GetConsole()->SetFGColorImpl(color);
                }

                void Console::SetTitle(const string str)
                {
                        GetConsole()->SetTitleImpl(str);
                }

                void Console::SetTitle(const char str[])
                {
                        GetConsole()->SetTitleImpl(str);
                }

                void Console::SetCursorPosition(int x,int y)
                {
                        GetConsole()->SetCursorPositionImpl(x, y);
                }

                void Console::Reset()
                {
                	GetConsole()->ResetImpl();
                }

                Console::Console()
                {
                }

                Console::~Console()
                {
                }

                Console *Console::GetConsole()
                {
                        if (!s_pConsole)
                        {
#if defined(ANDROID_PLATFORM)
                                s_pConsole = new AndroidConsole();
#elif defined(LINUX_PLATFORM)
                                s_pConsole = new LinuxConsole();
#elif defined(WINDOWS_PLATFORM)
                                s_pConsole = new WindowsConsole();
#else
                                s_pConsole = new StubConsole();
#endif
                        }
                        return s_pConsole;
                }
        }
}
