#ifndef INC_EVENTMANAGER_H
#define INC_EVENTMANAGER_H

#include <list>
#include "Event.h"
#include "EventQueue.h"

namespace EventManager {
	Event* decode(char* data);
	int encode(Event* e, char* data);
	Event* createEvent(event_t t);
	MoveEvent* createMoveEvent(int entityId, direction_t dir);
	ScoreEvent* createScoreEvent(int p, score_t s);
	CollisionEvent* createCollisionEvent(collision_t col, float x, float y);
	TimeUpdateEvent* createTimeUpdateEvent(float time);
	PuckUpdateEvent* createPuckUpdateEvent(float vx, float vy, float vz);
	PuckPosEvent* createPuckPosEvent(float x, float y, float z);
	BoostEvent* createBoostEvent(int player);
	Event* createJoinEvent();
	Event* createExplosionEvent();
	Event* createCameraToggleEvent();
	Event* createPauseEvent();
}
#endif // INC_EVENTMANAGER_H
