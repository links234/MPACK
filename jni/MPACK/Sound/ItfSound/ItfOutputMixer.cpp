#if defined(WINDOWS_PLATFORM) || defined(LINUX_PLATFORM)

#include "ItfOutputMixer.hpp"

#include "ItfSoundService.hpp"
#include "ItfAudioControllers.hpp"

using namespace std;

namespace MPACK
{
	namespace Sound
	{
		OutputMixer *OutputMixer::s_outputMixer=NULL;
		unordered_set<OutputMixer*> OutputMixer::s_objects;

		OutputMixer::OutputMixer()
			: m_pVolumeController(VolumeController::GetSentinel())
		{
			s_objects.insert(this);
		}

		OutputMixer::~OutputMixer()
		{
			if(m_pVolumeController!=VolumeController::GetSentinel())
			{
				delete m_pVolumeController;
				m_pVolumeController=VolumeController::GetSentinel();
			}
			s_objects.erase(this);
		}

		VolumeController* OutputMixer::Volume() const
		{
			return m_pVolumeController;
		}

		OutputMixer* OutputMixer::GetOutputMixer()
		{
			if(!s_outputMixer)
			{
				s_outputMixer = new OutputMixer();
			}
			return s_outputMixer;
		}

		void OutputMixer::DestroyOutputMixer()
		{
			if(s_outputMixer)
			{
				delete s_outputMixer;
				s_outputMixer=NULL;
			}
		}

		void OutputMixer::LoadControllers()
		{
			m_pVolumeController = new VolumeController();
		}

		void OutputMixer::Cleanup()
		{
			vector<OutputMixer*> allObjects;
			allObjects.reserve(s_objects.size());
			for(unordered_set<OutputMixer*>::iterator it=s_objects.begin();it!=s_objects.end();++it)
			{
				allObjects.push_back(*it);
			}
			for(vector<OutputMixer*>::iterator it=allObjects.begin();it!=allObjects.end();++it)
			{
				delete (*it);
			}
		}
	}
}

#endif
