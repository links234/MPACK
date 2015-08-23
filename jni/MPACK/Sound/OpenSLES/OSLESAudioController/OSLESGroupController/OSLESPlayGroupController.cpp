#ifdef ANDROID_PLATFORM

#include "OSLESPlayGroupController.hpp"

#include "OSLESGroupController.hpp"
#include "OSLESAudioPlayer.hpp"
#include "OSLESPlayController.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		PlayGroupController::PlayGroupController(GroupController *groupController)
			: m_pGroupController(groupController)
		{
		}

		PlayGroupController::~PlayGroupController()
		{
		}

		ReturnValue PlayGroupController::Start()
		{
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Play()->Start()==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}

		ReturnValue PlayGroupController::Resume()
		{
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Play()->Resume()==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}

		ReturnValue PlayGroupController::Pause()
		{
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Play()->Pause()==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}

		ReturnValue PlayGroupController::Stop()
		{
			ReturnValue retVal=RETURN_VALUE_OK;
			for(unordered_set<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				if((*it)->Play()->Stop()==RETURN_VALUE_KO)
				{
					retVal=RETURN_VALUE_KO;
				}
			}
			return retVal;
		}
	}
}

#endif
