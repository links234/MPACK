#include "MPACK.hpp"
#include "DemoApplication.hpp"

int result = 0;
Game::DemoApplication demoApplication;

MPACK_MAIN
{
	MPACK_INITIALIZE;

	MPACK_RUN(&demoApplication, result);

    MPACK_SHUTDOWN;

    MPACK_RETURN(result);
}
