#ifdef ANDROID_PLATFORM

#include "OSLESOutputMixer.hpp"

#include "OSLESSoundService.hpp"
#include "Global.hpp"
#include "Context.hpp"

#include "OSLESAudioControllers.hpp"

using namespace std;

namespace MPACK
{
	namespace Sound
	{
		OutputMixer *OutputMixer::s_outputMixer=NULL;
		unordered_set<OutputMixer*> OutputMixer::s_objects;

		OutputMixer::OutputMixer()
			: m_outputMixerObj(NULL),
			  m_pVolumeController(VolumeController::GetSentinel())
		{
			s_objects.insert(this);
		}

		OutputMixer::~OutputMixer()
		{
			if(m_outputMixerObj)
			{
				if(m_pVolumeController!=VolumeController::GetSentinel())
				{
					delete m_pVolumeController;
					m_pVolumeController=VolumeController::GetSentinel();
				}
				(*m_outputMixerObj)->Destroy(m_outputMixerObj);
				m_outputMixerObj = NULL;
				m_outputMixerObj=NULL;
			}
			s_objects.erase(this);
		}

		SLObjectItf OutputMixer::GetObjectItf() const
		{
			return m_outputMixerObj;
		}

		VolumeController* OutputMixer::Volume() const
		{
			return m_pVolumeController;
		}

		OutputMixer* OutputMixer::GetOutputMixer()
		{
			SLresult res = 0;

			if(!s_outputMixer)
			{
				s_outputMixer = new OutputMixer();

				const SLuint32      outputMixerIIDCount = 0;
				const SLInterfaceID outputMixerIIDs[]   = {};
				const SLboolean     outputMixerReqs[]   = {};

				SLEngineItf &engine=Global::pContext->pSoundService->GetOpenSLEngine();

				res = (*engine)->CreateOutputMix(engine, &s_outputMixer->m_outputMixerObj, outputMixerIIDCount, outputMixerIIDs, outputMixerReqs);
				if(res != SL_RESULT_SUCCESS)
				{
					LOGE("OutputMixer::GetOutputMixer() at (*engine)->CreateOutputMix");
					goto ERROR;
				}
				res = (*s_outputMixer->m_outputMixerObj)->Realize(s_outputMixer->m_outputMixerObj, SL_BOOLEAN_FALSE);
				if(res != SL_RESULT_SUCCESS)
				{
					LOGE("OutputMixer::GetOutputMixer() at (*s_outputMixer->m_outputMixerObj)->Realize");
					goto ERROR;
				}

				s_outputMixer->LoadControllers();
			}
			return s_outputMixer;

		ERROR:
			LOGE("OutputMixer::GetOutputMixer() error: res = %d",res);
			delete s_outputMixer;
			s_outputMixer=NULL;
			return NULL;
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
			m_pVolumeController = new VolumeController(m_outputMixerObj);
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
