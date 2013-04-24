#include "Enemy.h"

using namespace Arsenal;

Enemy::Enemy(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
			MoveBehaviour* behaviour, int maxHP)
		: mMaxHP(maxHP), mBehaviour(behaviour) {
	// Modify bullet behaviour
	initPhysics(dynamics, btVector3(2,2,2));

	// Convert the ID into a string
	std::string idString = "BOX-"+getIDStr();

	mRender = scene->createEntity(idString,Ogre::SceneManager::PT_CUBE);
	mNode = scene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mNode->setScale(0.1f,0.1f,0.1f);
	mRender->setCastShadows(true);

	setPos(0,0,zSpawn);
}

Enemy::~Enemy() {
	
}

void Enemy::update(float delta) {
	mBehaviour->update(delta, this);
	Entity::update(delta);
}