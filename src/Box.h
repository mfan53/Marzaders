#ifndef INC_ARSENAL_BOX_H
#define INC_ARSENAL_BOX_H

#include "Entity.h"

namespace Arsenal {
	class Box : public Entity {
	public:
		Box(Ogre::SceneManager*, btDiscreteDynamicsWorld*, float, float);
		virtual ~Box();
		void update(float delta);

		static const float Z_POS = -30; // Default z position for a box
		static const float SIZE = 20; // Default size of a box
		static const int MAX_HP = 3; // Maximum HP of a box

		int getHP() { return hp; }

	private:
		int hp; // The current hp of the box
	};
}

#endif // INC_ARSENAL_BOX_H
