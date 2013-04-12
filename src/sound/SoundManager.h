#ifndef INC_SOUNDMANAGER_H
#define INC_SOUNDMANAGER_H  

#include <stdio.h>
#include <stdlib.h>
#include <vector>
//#include <hash_map>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Sound.h"

#define MUS_PLASMA "../../res/music/plasma.ogg"
#define MUS_SWINGIN_FERRET "../../res/music/cable-swingin-ferret.ogg"
#define SND_BASS_DRUM "../../res/sounds/808-bassdrum.wav"
#define SND_CLAP "../../res/sounds/808-clap.wav"
#define SND_HI_HAT "../res/sounds/808-hihat.wav"
#define SND_PIANO_HIT "../../res/sounds/pianohit.wav"
#define SND_BEEP "../../res/sounds/beep.wav"
#define SND_EXPLOSION "../../res/sounds/explosion.wav"
#define SND_METAL_PLATE "../../res/sounds/metalplate.wav"
#define SND_POP "../../res/sounds/pop.wav"

using namespace std;
namespace Arsenal {
	class SoundManager {
		protected:
			//hash_map <char *, Sound*>;
			// TODO: replace the vector of sounds with a hashmap
			vector<Sound *> mSounds;
			int audio_rate;
			Uint16 audio_format;
			int audio_channels;
			int audio_buffers;
			int mNumChannels;
			int mCurrentChannel;

			void init(int channels);
			static void musicDone();
			static void channelFinished(int channel);
		public:
			SoundManager();
			SoundManager(int numChannels);
			virtual ~SoundManager();

			Sound *createSound(const char *file);
			/*
			 * 0 <= vol <= 128
			 * sets volume for all sounds
			*/
			void setSoundVolume(int vol);
			int loadMusic(const char *file);
			/* numTimes = -1 -> Loop continuously, otherwise intuitive */
			void playMusic(int numTimes);
			void pauseMusic();
			void resumeMusic();
			void switchMusic(const char *file, int numTimes);
			void stopMusic(bool fade);
			/* 0 <= vol <= 128 */
			void setMusicVolume(int vol);
			void closeAudio();
			int getNumChannels() {return mNumChannels;}

			static Mix_Music *music;
	};
}

#endif // INC_SOUNDMANAGER_H
