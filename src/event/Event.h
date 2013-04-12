#ifndef INC_EVENT_MANAGER_EVENT_H
#define INC_EVENT_MANAGER_EVENT_H

namespace EventManager {
	enum event_t {
		MOVE = 0,
		BOOST = 1,
		COLLISION = 2,
		SCORE = 3,
		EXPLOSION = 4,
		TIMER_TICK = 5,
		MENU_SELECTION = 6,
		CAMERA_ANGLE_TOGGLE = 7,
		JOIN = 8,
		PUCK_UPDATE = 9,
		PAUSE = 10,
		PUCK_POS = 11
	};

	enum direction_t {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, NONE = 4};
	enum collision_t {WALL = 0, PADDLE = 1};
	enum score_t {PLUS_ONE = 0, MINUS_THREE = 1};

	struct Event {
		event_t type;
		Event() {};
		Event(event_t t) : type(t) {}
		// EXPLOSION, CAMERA_ANGLE_TOGGLE, JOIN
	};
	struct MoveEvent : Event {
		int entityId;
		direction_t dir;
		MoveEvent(int eid, direction_t d) : Event(MOVE), entityId(eid), dir(d) {} 
	};
	struct ScoreEvent : Event {
		int player;
		score_t score;
		ScoreEvent(int p, score_t s) : Event(SCORE), player(p), score(s) {}
	};
	struct CollisionEvent : Event {
		collision_t col;
		float xpos, ypos;
		CollisionEvent(collision_t c, float x, float y) : Event(COLLISION), 
			col(c), xpos(x), ypos(y) {}
	};
	struct TimeUpdateEvent : Event {
		float time;
		TimeUpdateEvent(float t) : Event(TIMER_TICK), time(t) {}
	};
	struct PuckUpdateEvent : Event {
		float x,y,z;
		PuckUpdateEvent(float vx, float vy, float vz) : Event(PUCK_UPDATE), 
			x(vx), y(vy), z(vz) {}
	};
	struct PuckPosEvent : Event {
		float x,y,z;
		PuckPosEvent(float x, float y, float z) : Event(PUCK_POS), x(x), y(y), z(z) {}
	};
	struct BoostEvent : Event {
		int player;
		BoostEvent(int p) : Event(BOOST), player(p) {}
	};
	
}
#endif // INC_EVENT_MANAGER_EVENT_H
