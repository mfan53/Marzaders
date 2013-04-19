#ifndef INC_ARSENAL_ENTITY_H
#define INC_ARSENAL_ENTITY_H

#include "btBulletDynamicsCommon.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreMesh.h>
#include <OgreSceneNode.h>
#include "sound/Sound.h"

namespace Arsenal {
	class Entity {
	public:
		Entity();
		virtual ~Entity();
		
		virtual void update(float delta);

		int getId() { return mID; }
		float getX();
		float getY();
		float getZ();
		float getXV();
		float getYV();
		float getZV();
		Ogre::SceneNode* getNode() { return mNode; };

		void setPos(float x, float y, float z);
		void setVel(float vx, float vy, float vz);

	protected:
		// The id of the Entity
		int mID;

		// A reference to the scene node that this Entity belongs to
		Ogre::SceneNode* mNode;
		// A reference to the dynamics world that this Entity belongs to
		btDiscreteDynamicsWorld* mDynamics;

		// The Ogre render component
		Ogre::Entity* mRender;
		// The bullet physics components
		btRigidBody* mBody;
		btCollisionShape* mShape;
		btDefaultMotionState* mMotion;
	};
}


#endif // INC_ARSENAL_ENTITY_H

