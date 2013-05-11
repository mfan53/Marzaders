#ifndef INC_ARSENAL_SPAWNER_H
#define INC_ARSENAL_SPAWNER_H

#include <vector>
#include "Entity.h"
#include "Timer.h"

namespace Arsenal {
	class Spawner {
	public:
		Spawner();
		Spawner(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
				std::list<Arsenal::Entity*>* entities);
		virtual ~Spawner();

		void update(float delta);

		static const float Z_POS = -2000; // Default z spawning position

	private:
		// The timer the spawner uses to decide when to spawn the next wave
		Arsenal::Timer m_timer;

		// The scene world that the Spawner will spawn entities for
		Ogre::SceneManager* m_scene;
		// The physics world that the Spawner will spawn entities for
		btDiscreteDynamicsWorld* m_dynamics;
		// Pointer to list of entities that the Spawner will add entites to
		std::list<Arsenal::Entity*>* m_list;
	};
}

#endif // INC_ARSENAL_SPAWNER_H
