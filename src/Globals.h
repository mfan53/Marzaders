#ifndef INC_ARSENAL_GLOBALS_H
#define INC_ARSENAL_GLOBALS_H

#include "event/EventManager.h"
#include "event/Event.h"
#include "event/EventQueue.h"
#include "sound/SoundManager.h"
#include "ScoreManager.h"
#include "AirTraffic.h"

namespace Arsenal {
	class Globals {
		public:
			static EventManager::EventQueue * gEventQueue;
			static AirTraffic* airInst;
	};
}

#endif  // INC_ARSENAL_GLOBALS_H
