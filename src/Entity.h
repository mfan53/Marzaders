#ifndef INC_ARSENAL_ENTITY_H
#define INC_ARSENAL_ENTITY_H

#include "btBulletDynamicsCommon.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreMesh.h>
#include <OgreSceneNode.h>
#include "sound/Sound.h"

namespace Arsenal {
	struct coord3f {
		float x;
		float y;
		float z;
		coord3f() {};
		coord3f(float xpos, float ypos, float zpos) : x(xpos), y(ypos), z(zpos) {}
	};

	class Entity {
	public:
		Entity();
		Entity(Ogre::SceneManager* scene, unsigned int hp, unsigned int attack);
		Entity(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
				btVector3 hitbox, unsigned int hp, unsigned int attack,
				btScalar mass=10, float xPos=0, float yPos=0, float zPos=0);
		virtual ~Entity();

		void destroyScene();
		void destroyPhysics();

		virtual void update(float delta);

		virtual void damage(unsigned int damage) { mDamage += damage; };

		int getId() const { return mID; }
		std::string getIDStr() const;
		float getX() const;
		float getY() const;
		float getZ() const;
		float getXV() const;
		float getYV() const;
		float getZV() const;
		float getBoundingRadius() const { return mBoundingRadius; }
		Ogre::SceneNode* getNode() const { return mNode; };
		Ogre::Entity* getRender() const { return mRender; };
		unsigned int getHP() const { return mHP; };
		unsigned int getDamage() const { return mDamage; };
		unsigned int getAttack() const { return mAttack; };
		float getStartX() {return mStartX;}
		bool isDead() const { return mHP == 0 ? false : mDamage >= mHP; };

		void setPos(float x, float y, float z);
		void setVel(float vx, float vy, float vz);

	protected:
		// The starting position of the Entity
		float mStartX;

		// The id of the Entity
		int mID;
		// The bounding radius of the Entity
		float mBoundingRadius;

		// The maximum hit points of the entity or 0 if invulnerable
		unsigned int mHP;
		// The amount of damage this entity has taken
		unsigned int mDamage;
		// The amount of damage this entity can deal
		unsigned int mAttack;

		// A reference to the OGRE scene that this Entity belongs to
		Ogre::SceneManager* mScene;
		// A reference to the dynamics world that this Entity belongs to
		btDiscreteDynamicsWorld* mDynamics;

		// A reference to the scene node that this Entity belongs to
		Ogre::SceneNode* mNode;

		// The Ogre render component
		Ogre::Entity* mRender;
		// The bullet physics components
		btRigidBody* mBody;
		btCollisionShape* mShape;
		btDefaultMotionState* mMotion;

		void initPhysics(btDiscreteDynamicsWorld* world, btVector3 hitbox,
				btScalar mass=10, float xPos=0, float yPos=0, float zPos=0);

	private:
		// True if physics has been initialized
		bool mPhysics;

		void initID();
	};
}

#endif // INC_ARSENAL_ENTITY_H
