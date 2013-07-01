#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "Context.hpp"
#include "Asset.hpp"
#include "Types.hpp"
#include "Sound.hpp"
#include "Random.hpp"

#include <vector>
#include <list>

using namespace std;

namespace Core
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
        list<vector<char> > mList;
        list<vector<char> >::iterator mCurTrackIt;
        PlayMode mPlayMode;
        bool mLoop;

        Sound* mSound;

        void useNewPlist();
        void updateSound();
    };
}
#endif
