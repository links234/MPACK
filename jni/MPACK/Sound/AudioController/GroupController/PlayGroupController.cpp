#include "PlayGroupController.hpp"

#include "GroupController.hpp"
#include "AudioPlayer.hpp"
#include "PlayController.hpp"

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
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Play()->Start();
			}
		}

		ReturnValue PlayGroupController::Resume()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Play()->Resume();
			}
		}

		ReturnValue PlayGroupController::Pause()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Play()->Pause();
			}
		}

		ReturnValue PlayGroupController::Stop()
		{
			for(vector<AudioPlayer*>::iterator it=m_pGroupController->m_objects.begin();it!=m_pGroupController->m_objects.end();++it)
			{
				(*it)->Play()->Stop();
			}
		}
	}
}
