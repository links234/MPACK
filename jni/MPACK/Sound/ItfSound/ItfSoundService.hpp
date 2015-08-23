#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFSOUNDSERVICE_HPP
#define MPACK_ITFSOUNDSERVICE_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class SoundService
		{
		public:
			SoundService();
			~SoundService();

			Core::ReturnValue Start();
			void Stop();
		};
	}
}

#endif

#endif
