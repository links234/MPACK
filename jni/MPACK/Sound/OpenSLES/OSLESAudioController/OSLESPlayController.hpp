#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESPLAYCONTROLLER_HPP
#define MPACK_OSLESPLAYCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class PlayController
		{
		public:
			PlayController(SLObjectItf object);
			~PlayController();

			bool IsSupported() const;

			Core::ReturnValue Start();
			Core::ReturnValue Resume();
			Core::ReturnValue Pause();
			Core::ReturnValue Stop();

			SLmillisecond GetPosition();
			SLmillisecond GetDuration();

			static PlayController* GetSentinel();

		private:
			PlayController();

			SLPlayItf m_interface;

			static PlayController s_sentinel;
		};
	}
}

#endif

#endif
