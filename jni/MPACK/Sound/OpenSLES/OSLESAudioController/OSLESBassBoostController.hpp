#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESBASSBOOSTERCONTROLLER_HPP
#define MPACK_OSLESBASSBOOSTERCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class BassBoostController
		{
		public:
			BassBoostController(SLObjectItf object);
			~BassBoostController();

			bool IsSupported() const;

			bool IsEnabled() const;
			Core::ReturnValue Enable();
			Core::ReturnValue Disable();
			Core::ReturnValue Toggle();
			Core::ReturnValue SetEnabled(bool enabled);
			Core::ReturnValue SetStrength(SLpermille strength);
			SLpermille GetStrength() const;

			static BassBoostController* GetSentinel();

		private:
			BassBoostController();

			SLBassBoostItf m_interface;
			bool m_enabled;
			SLpermille m_strength;

			static BassBoostController s_sentinel;
		};
	}
}

#endif

#endif
