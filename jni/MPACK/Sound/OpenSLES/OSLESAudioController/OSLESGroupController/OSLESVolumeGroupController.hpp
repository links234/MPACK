#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESVOLUMEGROUPCONTROLLER_HPP
#define MPACK_OSLESVOLUMEGROUPCONTROLLER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class GroupController;
		class VolumeController;
		class StereoGroupController;
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

			StereoGroupController* Stereo() const;

		protected:
			VolumeGroupController(GroupController *groupController);

			GroupController *m_pGroupController;
			StereoGroupController *m_pStereoGroupController;

			friend class GroupController;
		};
	}
}

#endif

#endif
