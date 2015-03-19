#ifndef MPACK_OUTPUTMIXER_HPP
#define MPACK_OUTPUTMIXER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class OutputMixer
		{
		public:
			~OutputMixer();

			SLObjectItf GetObjectItf() const;

			static OutputMixer* GetOutputMixer();
			static void DestroyOutputMixer();

		private:
			OutputMixer();

			SLObjectItf m_outputMixerObj;

			static OutputMixer *s_outputMixer;
		};
	}
}

#endif
