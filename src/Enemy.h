#ifndef INC_ARSENAL_ENEMY_H
#define INC_ARSENAL_ENEMY_H

#include "Entity.h"
#include "behaviour/MoveBehaviour.h"
#include "Plasma.h" // For access to coord3f. Should clean this up.

namespace Arsenal {
	class Enemy : public Entity {
	public:
		Enemy(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
				MoveBehaviour* behaviour, float xPos, float yPos, float zPos, unsigned int hp = 1,
				unsigned int atk = 1);
		virtual ~Enemy();
		void update(float delta);
		float getWidth();

	private:
		// Enemy spawn location on the z axis
		//const static float zSpawn = -2000;

		MoveBehaviour* mBehaviour;
		void setColor();
		const static int maxColors = 5;
		const static int minColors = 1;
		int color;
	};
}

#endif // INC_ARSENAL_ENEMY_H
