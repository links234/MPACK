#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "Context.hpp"
#include "Asset.hpp"
#include "Types.hpp"
#include "Sound.hpp"

namespace Core
{
    class Playlist
    {
    public:
    	Playlist(const char* pPath);
    	~Playlist();

        const char* GetPath();


        Sound* GetSound();
        Sound* Next();
        Sound* Prev();

    private:
        Asset mResource;
        uint8_t* mRawList; off_t mLength;
        char **mList;
        int mNumTracks, mCurTrack;
        Sound* mSound;

    };
}
#endif
