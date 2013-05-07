#ifndef INC_ARSENAL_BOX_H
#define INC_ARSENAL_BOX_H

#include "Entity.h"

namespace Arsenal {
	class Box : public Entity {
	public:
		Box(Ogre::SceneManager*, btDiscreteDynamicsWorld*, float, float);
		virtual ~Box();
		void update(float delta);

		static const float Z_POS = -100; // Default z position for a box
		static const float SIZE = 25; // Default size of a box

		static const unsigned int HP = 3;
		static const unsigned int ATK = 1;
	};
}

#endif // INC_ARSENAL_BOX_H
