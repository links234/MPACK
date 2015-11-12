#ifdef LINUX_PLATFORM

#include "LinuxConsole.hpp"

#include <iostream>
#include <sstream>

using namespace std;

namespace MPACK
{
        namespace Core
        {
                LinuxConsole::LinuxConsole()
                {
                        m_BGColor = "30";
                        m_FGColor = "47";
                }

                LinuxConsole::~LinuxConsole()
                {
                }

                void LinuxConsole::ClearImpl()
                {
                        cout << "\033[2J";
                }

                void LinuxConsole::SetBGColorImpl(const BGColor color)
                {
                        switch(color)
                        {
                                default:
                                case BG_BLACK:
                                        m_BGColor = "40";
                                break;
                                case BG_BLUE:
                                        m_BGColor = "44";
                                break;
                                case BG_CYAN:
                                        m_BGColor = "46";
                                break;
                                case BG_GREEN:
                                        m_BGColor = "42";
                                break;
                                case BG_MAGENTA:
                                        m_BGColor = "45";
                                break;
                                case BG_RED:
                                        m_BGColor = "41";
                                break;
                                case BG_WHITE:
                                        m_BGColor = "47";
                                break;
                                case BG_YELLOW:
                                        m_BGColor = "43";
                                break;
                        }
                        UpdateColor();
                }

                void LinuxConsole::SetFGColorImpl(const FGColor color)
                {
                        switch(color)
                        {
                                case FG_BLACK:
                                        m_FGColor = "30";
                                break;
                                case FG_BLUE:
                                        m_FGColor = "34";
                                break;
                                case FG_CYAN:
                                        m_FGColor = "36";
                                break;
                                case FG_GREEN:
                                        m_FGColor = "32";
                                break;
                                case FG_MAGENTA:
                                        m_FGColor = "35";
                                break;
                                case FG_RED:
                                        m_FGColor = "31";
                                break;
                                default:
                                case FG_WHITE:
                                        m_FGColor = "37";
                                break;
                                case FG_YELLOW:
                                        m_FGColor = "33";
                                break;
                        }
                        UpdateColor();
                }

                void LinuxConsole::SetTitleImpl(const string str)
                {
                        cout << "\033]0;\0" << str << "\x07\0";
                }

                void LinuxConsole::SetTitleImpl(const char str[])
                {
                        cout << "\033]0;\0" << str << "\x07\0";
                }

                void LinuxConsole::SetCursorPositionImpl(int x,int y)
                {
                		stringstream str;
                		str << "\033[" << x << ";" << y << "H";
                		cout << str.str();
                }

                void LinuxConsole::ResetImpl()
                {
                	string reset = "\e[0m";
                	cout << reset;
                }

                void LinuxConsole::UpdateColor()
                {
                        string clr = "\033[";
                        clr += m_BGColor;
                        clr += ";";
                        clr += m_FGColor;
                        clr += "m";
                        cout << clr;
                }
        }
}

#endif
