#ifndef MPACK_VOLUMEGROUPCONTROLLER_HPP
#define MPACK_VOLUMEGROUPCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class GroupController;
		class VolumeController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class VolumeGroupController
		{
		public:
			~VolumeGroupController();

			Core::ReturnValue ToggleMute();
			Core::ReturnValue Mute();
			Core::ReturnValue Unmute();
			Core::ReturnValue SetMute(SLboolean mute);

			Core::ReturnValue Set(double linear);

			Core::ReturnValue EnableStereo();
			Core::ReturnValue DisableStereo();
			Core::ReturnValue ToggleStereo();
			Core::ReturnValue SetEnabledStereo(bool enabled);
			Core::ReturnValue SetStereoPosition(SLpermille stereoPosition);

		protected:
			VolumeGroupController(GroupController *groupController);

			GroupController *m_pGroupController;

			friend class GroupController;
		};
	}
}

#endif
