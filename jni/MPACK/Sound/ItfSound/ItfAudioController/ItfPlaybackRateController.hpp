#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFPLAYBACKRATECONTROLLER_HPP
#define MPACK_ITFPLAYBACKRATECONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class PlaybackRateController
		{
		public:
			PlaybackRateController();
			~PlaybackRateController();

			bool IsSupported() const;

			Core::ReturnValue Set(double value);
			double Get() const;

			static PlaybackRateController* GetSentinel();

		private:
			double m_value;
			double m_minValue;
			double m_maxValue;

			static PlaybackRateController s_sentinel;
		};
	}
}

#endif

#endif
