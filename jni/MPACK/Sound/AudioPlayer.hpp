#ifndef MPACK_AUDIOPLAYER_HPP
#define MPACK_AUDIOPLAYER_HPP

#include "Types.hpp"

namespace MPACK
{
	namespace Sound
	{
		class AudioPlayer
		{
		public:
			AudioPlayer();
			~AudioPlayer();

			std::string GetPath() const;

			Core::ReturnValue Load(std::string path);
			void Unload();

			Core::ReturnValue Start();
			Core::ReturnValue Resume();
			Core::ReturnValue Pause();
			Core::ReturnValue Stop();

		private:
			std::string m_path;

			SLObjectItf m_audioPlayerObj;
			SLPlayItf m_audioPlayer;
		};
	}
}

#endif
