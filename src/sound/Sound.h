#ifndef INC_SOUND_H
#define INC_SOUND_H

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"

class Sound {
protected:
	const char *mFile;
	bool mPaused;
	bool mPlaying;
	Mix_Chunk *mChunk;
	int mChannelId;
public:
	Sound();
	~Sound();
	Sound(const char *file, Mix_Chunk *chunk, int channelId);
	/* numTimes = -1 -> Loop continuously, otherwise intuitive */
	void play(int numTimes);
	void pause();
	void resume();
	void stop();
	int getId() {return mChannelId;}
	const char *getFileName() {return mFile;}
	bool isPaused() {return mPaused;}
	bool isPlaying() {return mPlaying;}
};
#endif // INC_SOUND_H
