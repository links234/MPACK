#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFPITCHCONTROLLER_HPP
#define MPACK_ITFPITCHCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class PitchController
		{
		public:
			PitchController();
			~PitchController();

			bool IsSupported() const;

			Core::ReturnValue Set(int value);
			int Get() const;

			static PitchController* GetSentinel();

		private:
			int m_minValue;
			int m_maxValue;
			int m_value;

			static PitchController s_sentinel;
		};
	}
}

#endif

#endif
