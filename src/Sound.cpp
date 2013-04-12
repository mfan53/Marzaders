#include "Sound.h"

Sound::Sound(const char *file, Mix_Chunk *chunk, int channelId) {
	mFile = file;
	mChunk = chunk;	
	mChannelId = channelId;
	mPlaying = false;
	mPaused = false;
}

Sound::~Sound() {
	//Mix_HaltChannel(mChannelId);
	//delete mChunk;
}

/*
 * -1 -> continuous loop
 * otherwise intuitive
*/
void Sound::play(int numTimes) {
//	if (mPlaying)
//		printf("Already playing bro.\n");
//	else
		Mix_PlayChannel(mChannelId, mChunk, numTimes);
	mPlaying = Mix_Playing(mChannelId);
	mPaused = false;
}

void Sound::pause() {
	if (mPaused)
		printf("Already paused bro.\n");
	if (!mPlaying)
		printf("Can't pause something that isn't playing, bro.\n");
	else {
		Mix_Pause(mChannelId);
		mPaused = Mix_Paused;	
	}
}

void Sound::resume() {
	if (!mPaused)
		printf("Sound is not paused so I can't resume bro.\n");
	else {
		Mix_Resume(mChannelId);
		mPaused = false;
	}
}

void Sound::stop() {
	Mix_HaltChannel(mChannelId);
	mChunk = NULL;
}
