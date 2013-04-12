#include <stdint.h>
#include <iostream>
#include "EventManager.h"

namespace EventManager {

	Event* createEvent(event_t t) {
		return new Event(t);
	}

	MoveEvent* createMoveEvent(int entityId, direction_t dir) {
		new MoveEvent(entityId, dir);
	}

	ScoreEvent* createScoreEvent(int p, score_t s) {
		return new ScoreEvent(p, s);
	}

	CollisionEvent* createCollisionEvent(collision_t col, int x, int y) {
		return new CollisionEvent(col, x, y);
	}

	TimeUpdateEvent* createTimeUpdateEvent(float time) {
		return new TimeUpdateEvent(time);
	}

	PuckUpdateEvent* createPuckUpdateEvent(float vx, float vy, float vz) {
		return new PuckUpdateEvent(vx, vy, vz);
	}

	PuckPosEvent* createPuckPosEvent(float x, float y, float z) {
		return new PuckPosEvent(x,y,z);
	}

	BoostEvent* createBoostEvent(int player) {
		return new BoostEvent(player);
	}

	Event* createJoinEvent() {
		return new Event(JOIN);
	}

	Event* createExplosionEvent() {
		return new Event(EXPLOSION);
	}

	Event* createCameraToggleEvent() {
		return new Event(CAMERA_ANGLE_TOGGLE);
	}

	Event* createPauseEvent() {
		return new Event(PAUSE);
	}
	
	int encode(Event* e, char* data) {
		int floatSize = sizeof(float);
		switch (e->type) {
			char* pCharTime;
			char* pX;
			char* pY;
			char* pZ;
			case MOVE:
				data[0] = ((uint8_t)e->type << 4) + ((MoveEvent*)e)->entityId;
				data[1] =  (uint8_t)((MoveEvent*)e)->dir;
				break;
			case SCORE:
				data[0] = ((uint8_t)e->type << 4)
					| ((uint8_t)(((ScoreEvent*)e)->player) << 2)
					| (uint8_t)((ScoreEvent*)e)->score;
				break;
			case TIMER_TICK:
				data[0] = ((uint8_t)e->type << 4);
				pCharTime = reinterpret_cast<char*>(&((TimeUpdateEvent*)e)->time);
				for (size_t i = 1; i <= floatSize; i++) {
					data[i] = *pCharTime;
					pCharTime++;
				}
				break;
			case PUCK_POS:
				data[0] = ((uint8_t)e->type << 4);
				pX = reinterpret_cast<char*>(&((PuckPosEvent*)e)->x);
				pY = reinterpret_cast<char*>(&((PuckPosEvent*)e)->y);
				pZ = reinterpret_cast<char*>(&((PuckPosEvent*)e)->z);
				for(size_t i = 1; i<= floatSize; i++) {
					data[i] = *pX;
					pX++;
				}
				for(size_t i = 1+floatSize; i<= 2*floatSize; i++) {
					data[i] = *pY;
					pY++;
				}
				for(size_t i = 1+(2*floatSize); i<= 3*floatSize; i++) {
					data[i] = *pZ;
					pZ++;
				}
				break;
			case PUCK_UPDATE:
				data[0] = ((uint8_t)e->type << 4);
				pX = reinterpret_cast<char*>(&((PuckUpdateEvent*)e)->x);
				pY = reinterpret_cast<char*>(&((PuckUpdateEvent*)e)->y);
				pZ = reinterpret_cast<char*>(&((PuckUpdateEvent*)e)->z);
				for(size_t i = 1; i<= floatSize; i++) {
					data[i] = *pX;
					pX++;
				}
				for(size_t i = 1+floatSize; i<= 2*floatSize; i++) {
					data[i] = *pY;
					pY++;
				}
				for(size_t i = 1+(2*floatSize); i<= 3*floatSize; i++) {
					data[i] = *pZ;
					pZ++;
				}
				break;
			case BOOST:
				data[0] = ((uint8_t)e->type << 4) |
						  (uint8_t)((BoostEvent*)e)->player;
				break;
			case JOIN:
			case EXPLOSION:
			case CAMERA_ANGLE_TOGGLE:
			case PAUSE:
				data[0] = ((uint8_t)e->type << 4);
				break;
		}
		return 15;
	}

	Event* decode(char* data) {
		event_t type = (event_t)((int)(data[0] >> 4 & 0xF));
		int floatSize = sizeof(float);
		switch(type) {
			float vx, vy, vz;
			case MOVE:
				return createMoveEvent(data[0],(direction_t)((int)data[1]));
			case SCORE:
				return createScoreEvent((data[0] >> 2) & 0x3,
										(score_t)(int)(data[0] & 0x3));
			case TIMER_TICK:
				return createTimeUpdateEvent(*reinterpret_cast<float*>(&data[1]));
			case PUCK_POS:
				vx = *reinterpret_cast<float*>(&data[1]);
				vy = *reinterpret_cast<float*>(&data[1+floatSize]);
				vz = *reinterpret_cast<float*>(&data[1+floatSize*2]);
				return createPuckPosEvent(vx, vy, vz);
			case PUCK_UPDATE:
				vx = *reinterpret_cast<float*>(&data[1]);
				vy = *reinterpret_cast<float*>(&data[1+floatSize]);
				vz = *reinterpret_cast<float*>(&data[1+floatSize*2]);
				return createPuckUpdateEvent(vx, vy, vz);
			case BOOST:
				return createBoostEvent(data[0] & 0xF);
			case JOIN:
			case EXPLOSION:
			case CAMERA_ANGLE_TOGGLE:
				return createEvent(type);
		}
		return new Event();
	}	
}
