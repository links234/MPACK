#include "MPACK.hpp"
#include "Application.hpp"

int result = 0;
Game::Application application;

MPACK_MAIN
{
	MPACK_INITIALIZE;

    MPACK_RUN(&application, result);

    MPACK_SHUTDOWN;

    MPACK_RETURN(result);
}
