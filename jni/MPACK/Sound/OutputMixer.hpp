#ifndef MPACK_OUTPUTMIXER_HPP
#define MPACK_OUTPUTMIXER_HPP

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

			static void DestroyAll();
		private:
			OutputMixer();

			void LoadControllers();

			SLObjectItf m_outputMixerObj;

			VolumeController *m_pVolumeController;

			static OutputMixer *s_outputMixer;

			static unordered_set<OutputMixer*> s_mixer;
		};
	}
}

#endif
