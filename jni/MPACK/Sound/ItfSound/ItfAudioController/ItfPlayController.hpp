#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFPLAYCONTROLLER_HPP
#define MPACK_ITFPLAYCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class PlayController
		{
		public:
			PlayController();
			~PlayController();

			bool IsSupported() const;

			Core::ReturnValue Start();
			Core::ReturnValue Resume();
			Core::ReturnValue Pause();
			Core::ReturnValue Stop();

			int GetPosition();
			int GetDuration();

			static PlayController* GetSentinel();

		private:
			static PlayController s_sentinel;
		};
	}
}

#endif

#endif
