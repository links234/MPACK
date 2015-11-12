#include "MPACK.hpp"

#include "DemoApplication.hpp"
#include "DemoConsoleApplication.hpp"

int result = 0;

MPACK_MAIN
{
	MPACK_INITIALIZE;

	MPACK_RUN(Game::DemoConsoleApplication, result);

    MPACK_SHUTDOWN;

    MPACK_RETURN(result);
}
