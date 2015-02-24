#ifndef MPACK_PLAYLIST_HPP
#define MPACK_PLAYLIST_HPP

#include "Types.hpp"

#include <vector>
#include <list>

namespace MPACK
{
	namespace Core
	{
		class Context;
	}

	namespace Sound
	{
		class Sound;
	}

	namespace Sound
	{
		enum PlayMode
		{
			FORWARD,
			BACKWARD,
			SHUFFLE
		};

		class Playlist
		{
		public:
			Playlist(const char* pPath);
			~Playlist();

			void Load(const char* pPath, bool forced); //"forced" ensures immediate change. Should be false if a sound from the plist is playing

			Sound* GetSound();

			bool Next();

			void setPlayMode(PlayMode p);

			void Print();
		private:

			char mCFile[40], mNFile[40]; // current file name, new file name
			std::list<std::vector<char> > mList;
			std::list<std::vector<char> >::iterator mCurTrackIt;
			PlayMode mPlayMode;
			bool mLoop;

			Sound* mSound;

			void useNewPlist();
			void updateSound();
		};
	}
}

#endif
