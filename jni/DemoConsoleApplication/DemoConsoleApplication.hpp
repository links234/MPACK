#ifndef DEMOCONSOLEAPPLICATION_HPP
#define DEMOCONSOLEAPPLICATION_HPP

#include "MPACK.hpp"

namespace Demo
{
    class ConsoleApplication : public MPACK::Core::ConsoleApplication
    {
    public:
    	ConsoleApplication();
    	~ConsoleApplication();

        int Main();
    };
}

#endif
