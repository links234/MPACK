#ifndef DEMOSEAMCARVINGAPPLICATION_HPP
#define DEMOSEAMCARVINGAPPLICATION_HPP

#include "MPACK.hpp"

namespace Demo
{
    class SeamCarvingApplication : public MPACK::Core::ConsoleApplication
    {
    public:
    	SeamCarvingApplication();
    	~SeamCarvingApplication();

        int Main();
    };
}

#endif
