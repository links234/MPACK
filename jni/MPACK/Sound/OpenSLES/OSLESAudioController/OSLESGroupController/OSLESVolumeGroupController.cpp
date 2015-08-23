#ifdef ANDROID_PLATFORM

#include "OSLESVolumeGroupController.hpp"

#include "OSLESAudioPlayer.hpp"
#include "OSLESGroupController.hpp"
#include "OSLESVolumeController.hpp"
#include "OSLESStereoGroupController.hpp"

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
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Volume()->ToggleMute()==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}

		ReturnValue VolumeGroupController::Mute()
		{
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Volume()->Mute()==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}

		ReturnValue VolumeGroupController::Unmute()
		{
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Volume()->Unmute()==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}

		ReturnValue VolumeGroupController::SetMute(SLboolean mute)
		{
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Volume()->SetMute(mute)==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}

		ReturnValue VolumeGroupController::Set(double linear)
		{
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Volume()->Set(linear)==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}

		StereoGroupController* VolumeGroupController::Stereo() const
		{
			return m_pStereoGroupController;
		}
	}
}

#endif
