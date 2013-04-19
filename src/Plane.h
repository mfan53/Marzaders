#ifndef INC_ARSENAL_PLANE_H
#define INC_ARSENAL_PLANE_H

#include "Entity.h"

namespace Arsenal {
	enum direction_t {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 4
	};
	class Plane : public Entity {
	public:

		Plane() {}
		Plane(Ogre::SceneManager* mSceneMgr,btDiscreteDynamicsWorld* dynamicsWorld,std::string name, Ogre::Camera* mCamera);
		virtual ~Plane();
		void update(float delta);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void stop(direction_t dir);


	private:
		//player 1 starting pos
		const static float xcoord = 0.0;
		const static float ycoord = 0.0;
		const static float zcoord = 0.0;

		bool mMoveUp, mMoveDown, mMoveLeft, mMoveRight;
	};
}

#endif // INC_ARSENAL_PLANE_H
