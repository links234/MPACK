#ifndef MPACK_PITCHCONTROLLER_HPP
#define MPACK_PITCHCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class PitchController
		{
		public:
			PitchController(SLObjectItf object);
			~PitchController();

			bool IsSupported() const;

			Core::ReturnValue Set(SLpermille value);
			SLpermille Get() const;

			static PitchController* GetSentinel();

		private:
			PitchController();

			SLPitchItf m_interface;
			SLpermille m_minValue;
			SLpermille m_maxValue;
			SLpermille m_value;

			static PitchController s_sentinel;
		};
	}
}

#endif
