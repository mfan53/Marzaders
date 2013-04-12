#ifndef INC_ARSENAL_ENTITY_H
#define INC_ARSENAL_ENTITY_H

#include "btBulletDynamicsCommon.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Sound.h"

namespace Arsenal {
	class Entity {
	protected:
		btDiscreteDynamicsWorld* dynamicsWorld;
		Ogre::SceneNode* mSceneNode;
		
		Ogre::Entity* mRenderEntity;
		btRigidBody* mBody;
		btCollisionShape* mShape;
		btDefaultMotionState * mMotionState;
		btVector3 mLocalInertia;
		btScalar mMass;
		bool isDynamic;
		int mId;

	public:
		Entity();
		virtual ~Entity();
		
		virtual void update(float delta);
		Ogre::SceneNode* getSceneNode() { return mSceneNode; };
		int getId() {return mId;}

		float getX();
		float getY();
		float getZ();
		void setPos(float x, float y, float z);
		float getXV();
		float getYV();
		float getZV();
		void setVel(float vx, float vy, float vz);

	};
}

#endif // INC_ARSENAL_ENTITY_H

