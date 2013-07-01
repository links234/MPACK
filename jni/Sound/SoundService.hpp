#ifndef SOUNDSERVICE_HPP
#define SOUNDSERVICE_HPP

#include "Sound.hpp"
#include "Types.hpp"
#include "Playlist.hpp"

//maximum number of simultaneouse sounds, excluding backgroud music
#define MAX_SOUNDS 5

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
        

        Sound* RegisterSound(const char* pPath);
        void PlaySound(Sound* pSound);
        
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
        // Sounds.
        Sound* mSounds[32]; int32_t mSoundCount;

        Playlist *mPlaylist;

        void SetBGMState(SLuint32 state);
        void SetSFXState(SLuint32 state);

        static void bqPlayerCallback(SLBufferQueueItf bq, void *context);
    };
}
#endif
