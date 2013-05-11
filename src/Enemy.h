#ifndef INC_ARSENAL_ENEMY_H
#define INC_ARSENAL_ENEMY_H

#include "Entity.h"
#include "behaviour/MoveBehaviour.h"
#include "Plasma.h"
#include <string.h>
#include <cmath>

namespace Arsenal {
	class Enemy : public Entity {
	public:
		Enemy(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
				MoveBehaviour* behaviour, float xPos, float yPos, float zPos, unsigned int hp = 1,
				unsigned int atk = 1);
		virtual ~Enemy();

		void update(float delta);

		void shoot(std::list<Arsenal::Entity*>* entities, float planeX, float planeY, float planeZ);

		float getWidth();

	private:
		MoveBehaviour* mBehaviour;
		void setColor();
		const static int maxColors = 5;
		const static int minColors = 1;
		int color;
	};
}

#endif // INC_ARSENAL_ENEMY_H
