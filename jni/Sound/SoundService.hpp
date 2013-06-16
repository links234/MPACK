#ifndef _PACKT_SOUNDSERVICE_HPP_
#define _PACKT_SOUNDSERVICE_HPP_

#include "Sound.hpp"
#include "Types.hpp"

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

        Status PlayBGM(const char* pPath);
        void StopBGM();

        Sound* RegisterSound(const char* pPath);
        void PlaySound(Sound* pSound);

    private:
        Status StartSoundPlayer();

    private:
        android_app* mApplication;

        // OpenSL ES engine.
        SLObjectItf mEngineObj; SLEngineItf mEngine;
        // Audio output.
        SLObjectItf mOutputMixObj;

        // Background music player.
        SLObjectItf mBGMPlayerObj; SLPlayItf mBGMPlayer;
        SLSeekItf mBGMPlayerSeek;


        //TODO: Struct with all player interfaces
        // Sound player.
        SLObjectItf mPlayerObj[MAX_SOUNDS]; SLPlayItf mPlayer[MAX_SOUNDS];
        SLBufferQueueItf mPlayerQueue[MAX_SOUNDS];
        // Sounds.
        Sound* mSounds[32]; int32_t mSoundCount;
    };
}
#endif
