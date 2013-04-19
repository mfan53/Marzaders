#ifndef INC_ARSENAL_PLASMA_H
#define INC_ARSENAL_PLASMA_H

#include "Entity.h"

namespace Arsenal {
	class Plasma : public Entity {
	public:

		Plasma() {}
		Plasma(Ogre::SceneManager* mSceneMgr, btDiscreteDynamicsWorld* dynamicsWorld,
				std::string name, const float x, const float y, const float z);
		virtual ~Plasma();
		void update(float delta);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void stop(direction_t dir);
		~Plasma() {} // We need to delete plasmas when they get out of range.

	private:
		//const static float xcoord = 0.0;
		//const static float ycoord = 0.0;
		//const static float zcoord = 0.0;

		//bool mMoveUp, mMoveDown, mMoveLeft, mMoveRight;
	};
}

#endif // INC_ARSENAL_PLASMA_H