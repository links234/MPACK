#include "MPACK.hpp"
#include "DemoApplication.hpp"

int result = 0;

MPACK_MAIN
{
	MPACK_INITIALIZE;

	MPACK_RUN(Game::DemoApplication, result);

    MPACK_SHUTDOWN;

    MPACK_RETURN(result);
}
