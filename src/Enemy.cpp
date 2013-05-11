#include "Enemy.h"
#include <iostream>

using namespace Arsenal;
using namespace std;

Enemy::Enemy(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
			MoveBehaviour* behaviour, float xPos, float yPos, float zPos, unsigned int hp, unsigned int atk) : 
			Entity(scene, dynamics, btVector3(15.3,15.3,15.3), hp, atk, 10, xPos, yPos, zPos), mBehaviour(behaviour) {
	// Convert the ID into a string
	std::string idString = "ENEMY-"+getIDStr();

	mRender = scene->createEntity(idString, Ogre::SceneManager::PT_CUBE);
	mRender->setCastShadows(true);
	mNode = scene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mNode->setScale(0.3f,0.3f,0.3f);
	mStartX = xPos;
	// color = (rand() % (maxColors - minColors + 1)) + minColors;
	setColor();
	//mRender->setMaterialName("Enemy/Water");
	enemy = true;
}

Enemy::~Enemy() {
	if(mBehaviour) delete mBehaviour;
}

void Enemy::update(float delta) {
	mBehaviour->update(delta, this);
	Entity::update(delta);
}

float Enemy::getWidth() {
	return mRender->getBoundingBox().getMaximum().x * 0.3 * 2;
}

void Enemy::setColor() {
	// switch(color) {
	// 	case 1:
	// 		mRender->setMaterialName("Color/Red");
	// 		break;
	// 	case 2:
	// 		mRender->setMaterialName("Color/Blue");
	// 		break;
	// 	case 3:
	// 		mRender->setMaterialName("Color/Green");
	// 		break;
	// 	case 4:
	// 		mRender->setMaterialName("Color/Yellow");
	// 		break;
	// 	case 5:
	// 		mRender->setMaterialName("Color/Black");
	// 		break;
	// 	default:
	// 		break;
	// }
	switch (mBehaviour->type) {
		case SHIFTER :
			mRender->setMaterialName("Enemy/Water");
		break;

		case FORWARD :
			mRender->setMaterialName("Enemy/RustySteel");
		break;
	}
}

string intToString(int x) {
	stringstream ss;
	ss << x;
	return ss.str();
}

void Enemy::shoot(int& bulletNumber, std::list<Arsenal::Entity*> * entities) {
	std::stringstream ss;
	string name;

	if (bulletNumber >= 999) bulletNumber = 1;
	cout << "about to create a Plasma" << endl;
	Arsenal::Plasma* p = new Arsenal::Plasma(mScene, mDynamics, intToString(bulletNumber),
					Arsenal::coord3f(getX(),getY(),getZ()+getWidth() + 5.0f),
					Arsenal::coord3f(0.0f, 0.0f, 100.0f), true);
	cout << "Created plasma" << endl;
	entities->push_back(p);
	cout << "Created and pushed back" << endl;
	bulletNumber += 1;
}