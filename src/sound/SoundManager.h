#ifndef INC_ARSENAL_SOUNDMANAGER_H
#define INC_ARSENAL_SOUNDMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Sound.h"

#define MUS_PLASMA "../res/music/plasma.ogg"
#define MUS_SWINGIN_FERRET "../res/music/cable-swingin-ferret.ogg"
#define SND_BASS_DRUM "../res/sounds/808-bassdrum.wav"
#define SND_CLAP "../res/sounds/808-clap.wav"
#define SND_HI_HAT "../res/sounds/808-hihat.wav"
#define SND_PIANO_HIT "../res/sounds/pianohit.wav"
#define SND_BEEP "../res/sounds/beep.wav"
#define SND_EXPLOSION "../res/sounds/explosion.wav"
#define SND_METAL_PLATE "../res/sounds/metalplate.wav"
#define SND_POP "../res/sounds/pop.wav"
#define SND_WELCOME "../res/sounds/welcome.wav"
#define SND_BULLET "../res/sounds/bullet.wav"

using namespace std;
namespace Arsenal {
    class SoundManager {
        private:
            static bool created;
            static SoundManager * sm;
        protected:
            SoundManager();
            SoundManager(int numChannels);
            ~SoundManager();

            static vector<Sound *> mSounds;
            static int audio_rate;
            static Uint16 audio_format;
            static int audio_channels;
            static int audio_buffers;
            static int mNumChannels;
            static int mCurrentChannel;

            static void musicDone();
            static void channelFinished(int channel);
        public:

            static SoundManager* getSoundManager(int numChannels = 10);

            static void init(int channels);
            static Sound *createSound(const char *file);
            /*
             * 0 <= vol <= 128
             * sets volume for all sounds
            */
            static void setSoundVolume(int vol);
            static int loadMusic(const char *file);
            /* numTimes = -1 -> Loop continuously, otherwise intuitive */
            static void playMusic(int numTimes);
            static void pauseMusic();
            static void resumeMusic();
            static void switchMusic(const char *file, int numTimes);
            static void stopMusic(bool fade);
            /* 0 <= vol <= 128 */
            static void setMusicVolume(int vol);
            static void closeAudio();
            static int getNumChannels() {return mNumChannels;}

            static Mix_Music *music;
    };
}

#endif // INC_ARSENAL_SOUNDMANAGER_H
