#ifndef MPACK_CONSOLE_HPP
#define MPACK_CONSOLE_HPP

#include <string>

namespace MPACK
{
        namespace Core
        {
                class Console
                {
                public:
                        enum BGColor {	BG_DEFAULT, BG_BLACK, BG_BLUE, BG_CYAN, BG_GREEN,
                        				BG_MAGENTA, BG_RED, BG_WHITE, BG_YELLOW };
                        enum FGColor {	FG_DEFAULT, FG_BLACK, FG_BLUE, FG_CYAN, FG_GREEN,
                        				FG_MAGENTA, FG_RED, FG_WHITE, FG_YELLOW };

                        static void Write(std::string str);
                        static void Write(int v);
                        static void Write(bool v);
                        static void Write(char str[]);
                        static void Write(char c);
                        static void Write(double d);
                        static void Write(float f);
                        static void WriteLine();
                        static void WriteLine(std::string str);
                        static void WriteLine(char str[]);

                        static char ReadKey();
                        static std::string ReadLine();

                        static void Cleanup();

                        static void Clear();

                        static void SetBGColor(const BGColor color);
                        static void SetFGColor(const FGColor color);
                        static void SetTitle(const std::string str);
                        static void SetTitle(const char str[]);
                        static void SetCursorPosition(int x,int y);
                        static void Reset();

                protected:
                        Console();
                        virtual ~Console();

                        virtual void ClearImpl() = 0;

                        virtual void SetBGColorImpl(const BGColor color) = 0;
                        virtual void SetFGColorImpl(const FGColor color) = 0;
                        virtual void SetTitleImpl(const std::string str) = 0;
                        virtual void SetTitleImpl(const char str[]) = 0;
                        virtual void SetCursorPositionImpl(int x,int y) = 0;
                        virtual void ResetImpl() = 0;

                        static Console *GetConsole();

                        static Console *s_pConsole;
                };
        }
}

#endif
