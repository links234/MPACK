#include "VolumeGroupController.hpp"

#include "AudioPlayer.hpp"
#include "GroupController.hpp"
#include "VolumeController.hpp"
#include "StereoGroupController.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		VolumeGroupController::VolumeGroupController(GroupController *groupController)
			: m_pGroupController(groupController)
		{
			m_pStereoGroupController = new StereoGroupController(groupController);
		}

		VolumeGroupController::~VolumeGroupController()
		{
			delete m_pStereoGroupController;
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

		StereoGroupController* VolumeGroupController::Stereo() const
		{
			return m_pStereoGroupController;
		}
	}
}
