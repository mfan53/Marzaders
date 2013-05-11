#include "Plasma.h"

using namespace Arsenal;
using namespace std;

Plasma::Plasma(Ogre::SceneManager* mSceneMgr, btDiscreteDynamicsWorld* dynamicsWorld,
				std::string name, const coord3f startPos, const coord3f startVelocity, bool isEnemyShot) {
	// OGRE
	mScene = mSceneMgr;
	mRender = mSceneMgr->createEntity(name,Ogre::SceneManager::PT_SPHERE);
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mRender->setCastShadows(true);
	if (isEnemyShot) {
		mRender->setMaterialName("Color/Red");
		scaleFactor = 0.03f;
	} else {
		mRender->setMaterialName("Examples/SphereMappedDroplet");
		scaleFactor = 0.04f;
	}
	
	mNode->scale(scaleFactor, scaleFactor, scaleFactor * 10);
	Ogre::Vector3 boundingBoxMaxCorner = scaleFactor * mRender->getBoundingBox().getMaximum();
	// Bullet

	initPhysics(dynamicsWorld,
		btVector3(boundingBoxMaxCorner.x, boundingBoxMaxCorner.y, boundingBoxMaxCorner.z),
		10, startPos.x, startPos.y, startPos.z);

	mBody->setRestitution(1);
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setLinearFactor(btVector3(0, 0, 1)); // only allow movement on z axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations
	velocity = coord3f(startVelocity);
	sceneMgr = mSceneMgr;
	paused = false;

	mHP = HP;
	mAttack = ATK;
}

Plasma::~Plasma() {
	
}

void Plasma::update(float delta) {
	// if (!hit) {
	// 	mBody->setLinearVelocity(btVector3(0, 0, -400.0f));
	// 	hit = true;
	// }
	if (paused) { 	
		Entity::update(0);	
		return;
	}
	if(getZ() <= WORLD_END) {
		damage(HP);
	}
	mBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
	Entity::update(delta);
}

void Plasma::pause() {
	paused = true;
	velX = mBody->getLinearVelocity().getX();
	velY = mBody->getLinearVelocity().getY();
	velZ = mBody->getLinearVelocity().getZ();
	mBody->setLinearVelocity(btVector3(0.0f,0.0f,0.0f));
}

void Plasma::unpause() {
	paused = false;
	mBody->setLinearVelocity(btVector3(velX,velY,velZ));
}


