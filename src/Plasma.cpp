#include "Plasma.h"

using namespace Arsenal;

Plasma::Plasma(Ogre::SceneManager* mSceneMgr, btDiscreteDynamicsWorld* dynamicsWorld,
				std::string name, const float x, const float y, const float z) {
	// OGRE
	mRender = mSceneMgr->createEntity(name,"geosphere8000.mesh");
	// float boundingRadius = mRender->getMesh()->getBoundingSphereRadius();
	// setBoundingRadius(boundingRadius);
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mRender->setCastShadows(true);
	mRender->setMaterialName("Examples/SphereMappedDroplet");
	float scaleFactor = 0.008f;
	mNode->scale(scaleFactor, scaleFactor, scaleFactor * 10);
	float boundingRadius = scaleFactor * mRender->getMesh()->getBoundingSphereRadius();
	setBoundingRadius(boundingRadius);
	// mNode->setPosition(Ogre::Vector3(x, y,z));

	// Bullet
	initPhysics(dynamicsWorld, btVector3(boundingRadius, boundingRadius, boundingRadius));

	mBody->setRestitution(1);
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setLinearFactor(btVector3(0, 0, 1)); // only allow movement on z axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations
	setPos(x,y,z);
}

Plasma::~Plasma() {
	
}

void Plasma::update(float delta) {
	mBody->setLinearVelocity(btVector3(0, 0, -400.0f));
	Entity::update(delta);
}