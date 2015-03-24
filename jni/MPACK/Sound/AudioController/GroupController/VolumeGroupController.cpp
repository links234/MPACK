#include "VolumeGroupController.hpp"

#include "AudioPlayer.hpp"
#include "GroupController.hpp"
#include "VolumeController.hpp"
#include "StereoController.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		VolumeGroupController::VolumeGroupController(GroupController *groupController)
			: m_pGroupController(groupController)
		{
		}

		VolumeGroupController::~VolumeGroupController()
		{
		}

		ReturnValue VolumeGroupController::ToggleMute()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->ToggleMute();
			}
		}

		ReturnValue VolumeGroupController::Mute()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Mute();
			}
		}

		ReturnValue VolumeGroupController::Unmute()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Unmute();
			}
		}

		ReturnValue VolumeGroupController::SetMute(SLboolean mute)
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->SetMute(mute);
			}
		}

		ReturnValue VolumeGroupController::Set(double linear)
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Set(linear);
			}
		}

		ReturnValue VolumeGroupController::EnableStereo()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->Enable();
			}
		}

		ReturnValue VolumeGroupController::DisableStereo()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->Disable();
			}
		}

		ReturnValue VolumeGroupController::ToggleStereo()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->Toggle();
			}
		}

		ReturnValue VolumeGroupController::SetEnabledStereo(bool enabled)
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->SetEnabled(enabled);
			}
		}

		ReturnValue VolumeGroupController::SetStereoPosition(SLpermille stereoPosition)
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->Set(stereoPosition);
			}
		}
	}
}
