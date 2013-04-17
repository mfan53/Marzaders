#ifndef INC_ARSENAL_ENTITY_H
#define INC_ARSENAL_ENTITY_H

#include "btBulletDynamicsCommon.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "sound/Sound.h"

namespace Arsenal {
	class Entity {
	public:
		Entity();
		virtual ~Entity();
		
		virtual void update(float delta);

		int getId() { return m_id; }
		float getX();
		float getY();
		float getZ();
		float getXV();
		float getYV();
		float getZV();
		Ogre::SceneNode* getNode() { return m_node; };

		void setPos(float x, float y, float z);
		void setVel(float vx, float vy, float vz);

	protected:
		// The id of the Entity
		int m_id;

		// A reference to the scene node that this Entity belongs to
		Ogre::SceneNode* m_node;
		// A reference to the dynamics world that this Entity belongs to
		btDiscreteDynamicsWorld* m_dynamics;

		// The Ogre render component
		Ogre::Entity* m_render;
		// The bullet physics components
		btRigidBody* m_body;
		btCollisionShape* m_shape;
		btDefaultMotionState* m_motion;
	};
}


#endif // INC_ARSENAL_ENTITY_H

