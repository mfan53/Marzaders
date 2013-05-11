#ifndef INC_ARSENAL_SPAWNER_H
#define INC_ARSENAL_SPAWNER_H

#include <vector>
#include "Entity.h"
#include "Timer.h"

namespace Arsenal {
	enum movementType {
		FORWARD = 1,
		SHIFTER = 2
	};
	class Spawner {
	public:
		Spawner();
		Spawner(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
				std::list<Arsenal::Entity*>* entities);
		virtual ~Spawner();

		void update(float delta);

		static const float Z_POS = -1000; // Default z spawning position

	private:
		// The timer the spawner uses to decide when to spawn the next wave
		Arsenal::Timer m_timer;

		// The scene world that the Spawner will spawn entities for
		Ogre::SceneManager* m_scene;
		// The physics world that the Spawner will spawn entities for
		btDiscreteDynamicsWorld* m_dynamics;
		// Pointer to list of entities that the Spawner will add entites to
		std::list<Arsenal::Entity*>* m_list;

		static const float gridStartX = -100.0f;
		static const float gridStartY = -50.0f;
		movementType currentMovement;
		float zSpeed;

		/*
		 * Spawns a grid of enemies.
		 * rowSpacing: horizontal spacing between enemies.
		 * colSpacing: vertical " ".
		*/
		void spawnEnemyGrid(int numRows, int numCols, float rowSpacing, float colSpacing);
	};
}

#endif // INC_ARSENAL_SPAWNER_H
