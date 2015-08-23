#ifdef ANDROID_PLATFORM

#include "OSLESGroupController.hpp"

#include "OSLESAudioPlayer.hpp"
#include "OSLESGroupControllers.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Sound
	{
		unordered_map<string, GroupController*> GroupController::s_group;
		unordered_set<GroupController*> GroupController::s_untrackedGroups;

		GroupController::GroupController(string name)
			: m_name(name)
		{
			m_pPlayGroupController = new PlayGroupController(this);
			m_pVolumeGroupController = new VolumeGroupController(this);
		}

		GroupController::~GroupController()
		{
			if(m_name=="")
			{
				s_untrackedGroups.erase(this);
			}
			else
			{
				s_group.erase(m_name);
			}

			delete m_pPlayGroupController;
			delete m_pVolumeGroupController;
		}

		void GroupController::Add(AudioPlayer *audioPlayer)
		{
			m_objects.insert(audioPlayer);
		}

		void GroupController::Remove(AudioPlayer *audioPlayer)
		{
			m_objects.erase(audioPlayer);
		}

		void GroupController::Clear()
		{
			m_objects.clear();
		}

		PlayGroupController* GroupController::Play() const
		{
			return m_pPlayGroupController;
		}

		VolumeGroupController* GroupController::Volume() const
		{
			return m_pVolumeGroupController;
		}

		GroupController* GroupController::Get(std::string name)
		{
			unordered_map<string,GroupController*>::iterator it=s_group.find(name);
			if(it!=s_group.end())
			{
				return it->second;
			}
			GroupController *pGroupController=new GroupController(name);
			s_group[name]=pGroupController;
			return pGroupController;
		}

		GroupController* GroupController::New()
		{
			GroupController *pGroupController = new GroupController();
			s_untrackedGroups.insert(pGroupController);
			return pGroupController;
		}

		void GroupController::Cleanup()
		{
			vector<GroupController*> allObjects;
			allObjects.reserve(s_untrackedGroups.size()+s_group.size());
			for(unordered_set<GroupController*>::iterator it=s_untrackedGroups.begin();it!=s_untrackedGroups.end();++it)
			{
				allObjects.push_back(*it);
			}
			for(unordered_map<string,GroupController*>::iterator it=s_group.begin();it!=s_group.end();++it)
			{
				allObjects.push_back(it->second);
			}
			for(vector<GroupController*>::iterator it=allObjects.begin();it!=allObjects.end();++it)
			{
				delete (*it);
			}
		}
	}
}

#endif
