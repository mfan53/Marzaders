#include "Enemy.h"
#include <iostream>

using namespace Arsenal;
using namespace std;

Enemy::Enemy(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
			MoveBehaviour* behaviour, float xPos, float yPos, float zPos, unsigned int hp, unsigned int atk)
		: Entity(scene, dynamics, btVector3(2,2,2), COL_ENEMY,
			COL_BOX | COL_SHIP | COL_PLASMA, hp, atk, 10, xPos, yPos, zPos),
			mBehaviour(behaviour) {
	// Convert the ID into a string
	std::string idString = "ENEMY-"+getIDStr();

	mRender = scene->createEntity(idString, Ogre::SceneManager::PT_CUBE);
	mRender->setCastShadows(true);
	mNode = scene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mNode->setScale(0.1f,0.1f,0.1f);
	//cout << "\n" << getIDStr() << " starting xpos: " << xPos << "\n" << endl;
	mStartX = xPos;
	color = (rand() % (maxColors - minColors + 1)) + minColors;
	setColor();
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

void Enemy::setColor() {
	switch(color) {
		case 1:
			mRender->setMaterialName("Color/Red");
			break;
		case 2:
			mRender->setMaterialName("Color/Blue");
			break;
		case 3:
			mRender->setMaterialName("Color/Green");
			break;
		case 4:
			mRender->setMaterialName("Color/Yellow");
			break;
		case 5:
			mRender->setMaterialName("Color/Black");
			break;
		default:
			break;
	}
}
