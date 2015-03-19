#ifndef MPACK_SOUNDSERVICE_HPP
#define MPACK_SOUNDSERVICE_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class OutputMixer;
		class AudioPlayer;
	}
}

namespace MPACK
{
	namespace Sound
	{
		class SoundService
		{
		public:
			SoundService();
			~SoundService();

			Core::ReturnValue Start();
			void Stop();

		private:
			SLEngineItf& GetOpenSLEngine();

			SLObjectItf m_engineObj;
			SLEngineItf m_engine;

			friend class OutputMixer;
			friend class AudioPlayer;
		};
	}
}

#endif
