#ifndef INC_ARSENAL_PLANE_H
#define INC_ARSENAL_PLANE_H

#include "Entity.h"

namespace Arsenal {
	class Plane : public Entity {
	public:
		Plane() {}
		Plane(Ogre::SceneManager* mSceneMgr,btDiscreteDynamicsWorld* dynamicsWorld,std::string name);
		virtual ~Plane();
		void update(float delta);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void stop();

	private:
		//player 1 starting pos
		const static float xcoord = 0.0;
		const static float ycoord = 0.0;
		const static float zcoord = 0.0;

		bool mMoveUp, mMoveDown, mMoveLeft, mMoveRight;
	};
}

#endif // INC_ARSENAL_PLANE_H
