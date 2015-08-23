#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#ifndef MPACK_ITFVOLUMEGROUPCONTROLLER_HPP
#define MPACK_ITFVOLUMEGROUPCONTROLLER_HPP

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
			Core::ReturnValue SetMute(bool mute);

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
