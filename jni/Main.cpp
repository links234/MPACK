#include "MPACK.hpp"
#include "DemoConsoleApplication.hpp"
#include "DemoAndroidApplication.hpp"
#include "DemoNetworkConsoleApplication.hpp"
#include "DemoSeamCarvingApplication.hpp"

int result = 0;

MPACK_MAIN
{
	MPACK_INITIALIZE;

	MPACK_RUN(Demo::SeamCarvingApplication, result);

    MPACK_SHUTDOWN;

    MPACK_RETURN(result);
}
