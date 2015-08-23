#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFSEEKCONTROLLER_HPP
#define MPACK_ITFSEEKCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class SeekController
		{
		public:
			SeekController();
			~SeekController();

			bool IsSupported() const;

			Core::ReturnValue SetPosition(int position);

			bool IsLoopingEnabled() const;
			Core::ReturnValue EnableLooping();
			Core::ReturnValue DisableLooping();
			Core::ReturnValue ToggleLooping();
			Core::ReturnValue SetEnabledLooping(bool enabled);

			static SeekController* GetSentinel();

		private:
			bool m_looping;

			static SeekController s_sentinel;
		};
	}
}

#endif

#endif
