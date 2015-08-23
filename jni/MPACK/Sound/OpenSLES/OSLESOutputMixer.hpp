#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESOUTPUTMIXER_HPP
#define MPACK_OSLESOUTPUTMIXER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class VolumeController;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class OutputMixer
		{
		public:
			~OutputMixer();

			SLObjectItf GetObjectItf() const;

			VolumeController* Volume() const;

			static OutputMixer* GetOutputMixer();
			static void DestroyOutputMixer();

			static void Cleanup();
		private:
			OutputMixer();

			void LoadControllers();

			SLObjectItf m_outputMixerObj;

			VolumeController *m_pVolumeController;

			static OutputMixer *s_outputMixer;

			static std::unordered_set<OutputMixer*> s_objects;
		};
	}
}

#endif

#endif
