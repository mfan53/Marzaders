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
			//~Plasma() {} // We need to delete plasmas when they get out of range.

		private:
			bool hit;
	};
}

#endif // INC_ARSENAL_PLASMA_H