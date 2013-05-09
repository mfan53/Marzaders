#ifndef INC_ARSENAL_PLASMA_H
#define INC_ARSENAL_PLASMA_H

#include "Entity.h"
#include <vector>

namespace Arsenal {
	// struct coord3f {
	// 	float x;
	// 	float y;
	// 	float z;
	// 	coord3f() {};
	// 	coord3f(float xpos, float ypos, float zpos) : x(xpos), y(ypos), z(zpos) {}
	// };

	class Plasma : public Entity {
		public:

			Plasma() {}
			Plasma(Ogre::SceneManager* mSceneMgr, btDiscreteDynamicsWorld* dynamicsWorld,
					std::string name, const coord3f, const coord3f startVelocity);
			virtual ~Plasma();
			void update(float delta);
			void pause();
			void unpause();
			std::string getID();
			//~Plasma() {} // We need to delete plasmas when they get out of range.

			static const unsigned int HP = 1;
			static const unsigned int ATK = 1;

			static const int WORLD_END = -2000;

		private:
			bool hit;
			coord3f velocity;
			Ogre::SceneManager* sceneMgr;

			float velX;
			float velY;
			float velZ;

			bool paused;
			std::string id;
	};
}

#endif // INC_ARSENAL_PLASMA_H
