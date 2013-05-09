#include "Enemy.h"
#include <iostream>

using namespace Arsenal;
using namespace std;

Enemy::Enemy(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
			MoveBehaviour* behaviour, float xPos, float yPos, float zPos, unsigned int hp, unsigned int atk)
		: Entity(scene, dynamics, btVector3(2,2,2), hp, atk),
		  mBehaviour(behaviour) {
	// Convert the ID into a string
	std::string idString = "ENEMY-"+getIDStr();

	mRender = scene->createEntity(idString, Ogre::SceneManager::PT_CUBE);
	mRender->setCastShadows(true);
	mNode = scene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mNode->setScale(0.1f,0.1f,0.1f);

	setPos(xPos, yPos, zPos);
	//cout << "\n" << getIDStr() << " starting xpos: " << xPos << "\n" << endl;
	mStartX = xPos;
}

Enemy::~Enemy() {
	if(mBehaviour) delete mBehaviour;
}

void Enemy::update(float delta) {
	mBehaviour->update(delta, this);
	Entity::update(delta);
}

float Enemy::getWidth() {
	return mRender->getBoundingBox().getMaximum().x * .01 * 2;
}