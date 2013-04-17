#ifndef INC_ARSENAL_SCOREMANAGER_H
#define INC_ARSENAL_SCOREMANAGER_H

#include "sound/Sound.h"
#include "event/EventManager.h"

namespace Arsenal {
	class ScoreManager {
	public:
		//ScoreManager();
		//ScoreManager(EventManager::EventQueue * eq);
		//~ScoreManager();
		static void netP1UpdateScore(EventManager::score_t delta);
		static void netP2UpdateScore(EventManager::score_t delta);
		static void p1UpdateScore(int delta);
		static void p2UpdateScore(int delta);
		static void reset();
		static void setScoreSound(Sound * sound) {mSound = sound;}

		static int getP1Score() { return p1Score; };
		static int getP2Score() { return p2Score; };
		static int getNumPlayed() { return numPlayed; };

	private:
		static int p1Score;
		static int p2Score;
		static int numPlayed;
		static Sound * mSound;
	};
}

#endif // INC_ARSENAL_SCOREMANAGER_H
