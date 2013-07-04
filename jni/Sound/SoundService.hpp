#ifndef SOUNDSERVICE_HPP
#define SOUNDSERVICE_HPP

#include "Sound.hpp"
#include "Types.hpp"
#include "Playlist.hpp"

#include <map>
#include <string>

#define SS_DBG

//maximum number of simultaneouse sounds, excluding backgroud music
#define MAX_SOUNDS 5

using namespace std;

namespace Core
{
    class SoundService
    {
    public:
        SoundService();
        ~SoundService();

        Status Start();
        void Stop();

        Status PlayBGMPlaylist(const char* pPath, bool forced = false); //uses new playlist for bgm. Chandg occurs after finishing current track if not forced
        

        void RegisterSound(const char* pPath);
        void UnregisterSound(const char* pPath);
        void PlaySFX(const char* pPath, bool load = false);
        
        void StopBGM();
        
        void PauseBGM();
        void PauseSFX();
        void PauseAll();

        void ResumeBGM();
        void ResumeSFX();
        void ResumeAll();

    private:
        Status StartSoundPlayers();
        Status StartBGMPlayer();

    private:
        android_app* mApplication;

        // OpenSL ES engine.
        SLObjectItf mEngineObj; SLEngineItf mEngine;
        // Audio output.
        SLObjectItf mOutputMixObj;

        // Background music player.
        SLObjectItf mBGMPlayerObj; SLPlayItf mBGMPlayer;
        SLBufferQueueItf mBGMPlayerQueue;

        //TODO: Struct with all player interfaces
        // Sound player.
        SLObjectItf mPlayerObj[MAX_SOUNDS]; SLPlayItf mPlayer[MAX_SOUNDS];
        SLBufferQueueItf mPlayerQueue[MAX_SOUNDS];
        Sound* tempSounds[MAX_SOUNDS];
        // Sounds.
        //Sound* mSounds[32]; int32_t mSoundCount;
        map<string, Sound*> mSounds;

        Playlist *mPlaylist;

        void SetBGMState(SLuint32 state);
        void SetSFXState(SLuint32 state);

        static void bqBGMPlayerCallback(SLBufferQueueItf bq, void *context);
        static void bqSFXPlayerCallback(SLBufferQueueItf bq, void *context);

    };
}
#endif
