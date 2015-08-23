#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESSEEKCONTROLLER_HPP
#define MPACK_OSLESSEEKCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class SeekController
		{
		public:
			SeekController(SLObjectItf object);
			~SeekController();

			bool IsSupported() const;

			Core::ReturnValue SetPosition(SLmillisecond position);

			bool IsLoopingEnabled() const;
			Core::ReturnValue EnableLooping();
			Core::ReturnValue DisableLooping();
			Core::ReturnValue ToggleLooping();
			Core::ReturnValue SetEnabledLooping(bool enabled);

			static SeekController* GetSentinel();

		private:
			SeekController();

			SLSeekItf m_interface;
			bool m_looping;

			static SeekController s_sentinel;
		};
	}
}

#endif

#endif
