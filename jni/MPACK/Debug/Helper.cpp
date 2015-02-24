#include "Helper.hpp"

#include "Debug.hpp"
#include "Log.hpp"

#include <unistd.h>

namespace MPACK
{
	namespace Debug
	{
		void WaitToConnect(int wait_time)
		{
			LOGI("Waiting for debugger to connect ...");

			int wait = 1;
			while (wait < wait_time)
			{
				wait++;
				usleep(1000000);

				LOGI(" ... second %d ... out of %d", wait, wait_time);
			}

			LOGI("Done waiting");
		}
	}
}
