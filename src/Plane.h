#ifndef INC_ARSENAL_PLANE_H
#define INC_ARSENAL_PLANE_H

#include "Entity.h"
#include "Plasma.h"
#include "sound/SoundManager.h"
#include <string.h>

namespace Arsenal {
	enum direction_t {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 4
	};
	enum shot_t {
		SINGLE = 0,
		SPRAY3 = 1,
		SPRAY5 = 2
	};

	class Plane : public Entity {
	public:

		Plane() {}
		Plane(Ogre::SceneManager* mSceneMgr,btDiscreteDynamicsWorld* dynamicsWorld,std::string name);
		virtual ~Plane();
		void shoot(std::list<Arsenal::Entity*>* entities);
		void update(float delta);
		void move(direction_t dir);
		void stop(direction_t dir);
		void setShot(shot_t shot) {shot_type = shot;}
		void reset();

	private:
		//player 1 starting pos
		const static float xcoord = 0.0;
		const static float ycoord = 0.0;
		const static float zcoord = 0.0;
		const static float mSpeed = 90.0;

		Sound * shootSound;

		Ogre::SceneManager* sceneManager;
		btDiscreteDynamicsWorld* dynWorld;

		shot_t shot_type;
		bool mMoveUp, mMoveDown, mMoveLeft, mMoveRight;

		std::string intToString(int x);
	};
}

#endif // INC_ARSENAL_PLANE_H
