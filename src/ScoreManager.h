#ifndef INC_ARSENAL_SCOREMANAGER_H
#define INC_ARSENAL_SCOREMANAGER_H

#include "sound/Sound.h"
#include "event/EventManager.h"

namespace Arsenal {
	class ScoreManager {
	public:
		ScoreManager();
		ScoreManager(EventManager::EventQueue * eq);
		~ScoreManager();
		void netP1UpdateScore(EventManager::score_t delta);
		void netP2UpdateScore(EventManager::score_t delta);
		void p1UpdateScore(int delta);
		void p2UpdateScore(int delta);
		void reset();
		void setScoreSound(Sound * sound) {mSound = sound;}

		int getP1Score() { return p1Score; };
		int getP2Score() { return p2Score; };
		int getNumPlayed() { return numPlayed; };

	private:
		EventManager::EventQueue * eventQueue;
		int p1Score;
		int p2Score;
		int numPlayed;
		Sound * mSound;
	};
}

#endif // INC_ARSENAL_SCOREMANAGER_H
