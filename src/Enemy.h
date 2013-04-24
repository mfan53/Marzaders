#ifndef INC_ARSENAL_ENEMY_H
#define INC_ARSENAL_ENEMY_H

#include "Entity.h"
#include "behaviour/MoveBehaviour.h"

namespace Arsenal {
	class Enemy : public Entity {
	public:
		Enemy(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
				MoveBehaviour* behaviour, int maxHP = 1);
		virtual ~Enemy();
		void update(float delta);

	private:
		// Enemy max HP
		const int mMaxHP;
		// Enemy spawn location on the z axis
		const static float zSpawn = -300;

		MoveBehaviour* mBehaviour;
	};
}

#endif // INC_ARSENAL_ENEMY_H
