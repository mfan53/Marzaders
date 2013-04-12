#include "SoundManager.h"
#include <iostream>

using namespace std;
using namespace Arsenal;
Mix_Music *SoundManager::music = NULL;

SoundManager::SoundManager() {
}

SoundManager::SoundManager(int numChannels) {
	init(numChannels);
}

SoundManager::~SoundManager() {
}

void SoundManager::init(int channels) {
	audio_rate = 22050;
	audio_format = AUDIO_S16;
	audio_channels = 2;
	audio_buffers = 4096;
	mNumChannels = channels;
	mCurrentChannel = 0;
	SDL_Init(SDL_INIT_AUDIO);

	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
		printf("Unable to open audio!\n");
		exit(1);
	}
	cout << "Audio opened successfully" << endl;
	Mix_AllocateChannels(mNumChannels);
   	Mix_HookMusicFinished(musicDone);
	Mix_ChannelFinished(channelFinished);
}

void SoundManager::musicDone() {
	Mix_HaltMusic();
	Mix_FreeMusic(SoundManager::music);
	SoundManager::music = NULL;
}

void SoundManager::channelFinished(int channel) {
}

int SoundManager::loadMusic(const char *file) {
	/* If there isn't music already loaded then load.
	 * otherwise halt and clear the current music and
	 * then load.
	*/
	if (SoundManager::music == NULL) {
		SoundManager::music = Mix_LoadMUS(file);
		if (!SoundManager::music)
			printf("Loading music failed: %s\n", Mix_GetError());
		else
			cout << "Loaded the music" << endl;
	} else {
		musicDone();
		this->loadMusic(file);
	}
	return 1;
}

/* numTimes = -1 -> infinite
 * " "		=  0 -> play once
*/
void SoundManager::playMusic(int numTimes) {
	Mix_FadeInMusic(SoundManager::music, numTimes, 2000);
}

void SoundManager::pauseMusic() {
	Mix_PauseMusic();
}

void SoundManager::resumeMusic() {
	Mix_ResumeMusic();
}

void SoundManager::switchMusic(const char *file, int numTimes) {
	loadMusic(file);
	playMusic(numTimes);
}

/*
 * 0 -> halt
 * 1 -> two second fade
*/
void SoundManager::stopMusic(bool fade) {
	if (fade) Mix_FadeOutMusic(2000);
	else Mix_HaltMusic();
}

void SoundManager::setMusicVolume(int vol) {
	vol = (vol > 128) ? 128 : ((vol < 0) ? 0 : vol);
	Mix_VolumeMusic(vol);
}

Sound * SoundManager::createSound(const char *file) {
	Mix_Chunk * chunkyChunk = Mix_LoadWAV(file);
	Sound * soundySound = new Sound(file, chunkyChunk, mCurrentChannel);
	mCurrentChannel += 1;
	mSounds.push_back(soundySound);
	return soundySound;
}

void SoundManager::setSoundVolume(int vol) {
	vol = (vol > 128) ? 128 : ((vol < 0) ? 0 : vol);
	Mix_Volume(-1, vol);
}

void SoundManager::closeAudio() {
	musicDone();
	Mix_HaltChannel(-1);
	for (int i = 0; i < mSounds.size(); i++) {
		Sound * sound = mSounds[i];
		delete sound;
	}
	Mix_CloseAudio();
	SDL_Quit();
}
