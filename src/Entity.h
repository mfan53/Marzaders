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
		Entity(btDiscreteDynamicsWorld* dynamics, btVector3 hitbox,
				btScalar mass = 10);
		virtual ~Entity();

		virtual void update(float delta);

		int getId() const { return mID; }
		std::string getIDStr() const;
		float getX() const;
		float getY() const;
		float getZ() const;
		float getXV() const;
		float getYV() const;
		float getZV() const;
		float getBoundingRadius() const {return mBoundingRadius;}
		Ogre::SceneNode* getNode() { return mNode; };

		void setPos(float x, float y, float z);
		void setVel(float vx, float vy, float vz);
		void setBoundingRadius(float r) {mBoundingRadius = r;}

	protected:
		// The id of the Entity
		int mID;
		float mBoundingRadius;

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

		void initPhysics(btDiscreteDynamicsWorld* world, btVector3 hitbox,
				btScalar mass = 10);

	private:
		// True if physics has been initialized
		bool mPhysics;

		void initID();
	};
}


#endif // INC_ARSENAL_ENTITY_H

