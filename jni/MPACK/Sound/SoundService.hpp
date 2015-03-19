#ifndef MPACK_SOUNDSERVICE_HPP
#define MPACK_SOUNDSERVICE_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class OutputMixer;
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

			Core::ReturnValue Test();

		private:
			SLEngineItf& GetOpenSLEngine();

			// OpenSL ES engine.
			SLObjectItf m_engineObj; SLEngineItf m_engine;

			// Background music player.
			SLObjectItf mBGMPlayerObj; SLPlayItf mBGMPlayer;
			SLBufferQueueItf mBGMPlayerQueue;

			friend class OutputMixer;
		};
	}
}

#endif
