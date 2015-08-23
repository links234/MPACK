#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFBASSBOOSTERCONTROLLER_HPP
#define MPACK_ITFBASSBOOSTERCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class BassBoostController
		{
		public:
			BassBoostController();
			~BassBoostController();

			bool IsSupported() const;

			bool IsEnabled() const;
			Core::ReturnValue Enable();
			Core::ReturnValue Disable();
			Core::ReturnValue Toggle();
			Core::ReturnValue SetEnabled(bool enabled);
			Core::ReturnValue SetStrength(int strength);
			int GetStrength() const;

			static BassBoostController* GetSentinel();

		private:
			bool m_enabled;
			int m_strength;

			static BassBoostController s_sentinel;
		};
	}
}

#endif

#endif
