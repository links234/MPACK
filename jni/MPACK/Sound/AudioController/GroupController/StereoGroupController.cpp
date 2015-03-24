#include "StereoGroupController.hpp"

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
		StereoGroupController::StereoGroupController(GroupController *pGroupController)
			: m_pGroupController(pGroupController)
		{
		}

		StereoGroupController::~StereoGroupController()
		{
		}

		ReturnValue StereoGroupController::Enable()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->Enable();
			}
		}

		ReturnValue StereoGroupController::Disable()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->Disable();
			}
		}

		ReturnValue StereoGroupController::Toggle()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->Toggle();
			}
		}

		ReturnValue StereoGroupController::SetEnabled(bool enabled)
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->SetEnabled(enabled);
			}
		}

		ReturnValue StereoGroupController::Set(SLpermille position)
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Volume()->Stereo()->Set(position);
			}
		}
	}
}
