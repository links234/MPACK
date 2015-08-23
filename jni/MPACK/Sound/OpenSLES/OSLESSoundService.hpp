#ifdef ANDROID_PLATFORM

#ifndef MPACK_OSLESSOUNDSERVICE_HPP
#define MPACK_OSLESSOUNDSERVICE_HPP

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

#endif

