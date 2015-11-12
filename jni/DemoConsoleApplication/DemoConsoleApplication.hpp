#ifndef DEMOCONSOLEAPPLICATION_HPP
#define DEMOCONSOLEAPPLICATION_HPP

#include "MPACK.hpp"

namespace Game
{
    class DemoConsoleApplication : public MPACK::Core::ConsoleApplication
    {
    public:
    	DemoConsoleApplication();
    	~DemoConsoleApplication();

        int Main();
    };
}

#endif
