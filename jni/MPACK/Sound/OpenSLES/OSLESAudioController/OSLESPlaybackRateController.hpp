#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESPLAYBACKRATECONTROLLER_HPP
#define MPACK_OSLESPLAYBACKRATECONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class PlaybackRateController
		{
		public:
			PlaybackRateController(SLObjectItf object);
			~PlaybackRateController();

			bool IsSupported() const;

			Core::ReturnValue Set(double value);
			double Get() const;

			static PlaybackRateController* GetSentinel();

		private:
			PlaybackRateController();

			SLPlaybackRateItf m_interface;
			double m_value;
			double m_minValue;
			double m_maxValue;

			static PlaybackRateController s_sentinel;
		};
	}
}

#endif

#endif
