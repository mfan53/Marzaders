#include "Plane.h"
#include "Globals.h"

using namespace Arsenal;
using namespace std;

Plane::Plane(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* world,
			std::string name) {
	dynWorld = world;
	shot_type = SINGLE;

	// OGRE
	mScene = scene;
	mRender = scene->createEntity(name,"RZR-002.mesh");
	float bounds = mRender->getMesh()->getBoundingSphereRadius();
	mNode = scene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mRender->setCastShadows(true);
	mNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
	//rotate the plane
	mNode->yaw(Ogre::Radian(M_PI));

	// Setup bullet
	initPhysics(world, btVector3(bounds,bounds,bounds), COL_SHIP, COL_ENEMY | COL_BULLET);
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setRestitution(1);
	mBody->setLinearFactor(btVector3(1,1,0)); // only allow movement on x,y axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations

	mMoveUp = false;
	mMoveDown = false;
	mMoveLeft = false;
	mMoveRight = false;

	mHP = 1;
	mAttack = 1;
	mDamage = 0;

	shootSound = SoundManager::getSoundManager()->createSound(SND_BULLET);

	//create shield
	/*Ogre::Entity* shield = scene->createEntity("shield",Ogre::SceneManager::PT_SPHERE);
	Ogre::SceneNode* snode = scene->getRootSceneNode()->createChildSceneNode();
	shield->setMaterialName("TransGold");
	snode->attachObject(shield);
	shield->setCastShadows(false);
	snode->scale(0.3f,0.3f,0.3f);
	mNode->addChild(snode);*/
}

Plane::~Plane() {

}

void Plane::update(float delta) {
	float y = 0;
	float x = 0;
	float yLowerBound = mRender->getBoundingBox().getMinimum().y;
	if (mMoveUp) {
		y += mSpeed;
	}
	if (mMoveDown && this->getY() + yLowerBound > Globals::floorY) {
		y -= mSpeed;
	}
	if (mMoveLeft) {
		x -= mSpeed;
	}
	if (mMoveRight) {
		x += mSpeed;
	}
	x = (getX() < -100 && x < 0) || (getX() > 100 && x > 0) ? 0 : x;
	y = (getY() < -100 && y < 0) || (getY() > 100 && y > 0) ? 0 : y;

	mBody->setLinearVelocity(btVector3(x, y, 0.0f));
	Entity::update(delta);
}

void Plane::move(direction_t dir) {
	switch (dir) {
		case UP:
			mMoveUp = true;
			break;
		case DOWN:  
			mMoveDown = true;
			break;
		case LEFT: 
			mMoveLeft = true;
			break;
		case RIGHT: 
			mMoveRight = true;
		break;
	}
}

void Plane::stop(direction_t dir) {
	switch (dir) {
		case UP:
			mMoveUp = false;
			break;
		case DOWN:  
			mMoveDown = false;
			break;
		case LEFT: 
			mMoveLeft = false;
			break;
		case RIGHT: 
			mMoveRight = false;
		break;
	}
}

string Plane::intToString(int x) {

	stringstream ss;
	ss << x;
	return ss.str();
}

void Plane::reset() {
	btTransform transform = mBody->getCenterOfMassTransform();
	transform.setOrigin(btVector3(xcoord,ycoord,zcoord));
	mBody->setCenterOfMassTransform(transform);
}

void Plane::shoot(int& bulletNumber, std::list<Arsenal::Entity*> * entities) {
	std::stringstream ss;
	string name;
	shootSound->play(0);

	if (bulletNumber >= 999) bulletNumber = 1;

	switch (shot_type) {

		case SINGLE: {
			Arsenal::Plasma* p = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX(),getY(),getZ()-20),
							Arsenal::coord3f(0.0f, 0.0f, -400.0f));
			entities->push_back(p);
			bulletNumber += 1;
			break;
		}

		case SPRAY3: {
			// Idea: Have the option to control angle of spray

			Arsenal::Plasma* left = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX()-5.0f, getY(), getZ()-20),
							Arsenal::coord3f(-50.0f, 0.0f, -400.0f));
			entities->push_back(left);
			bulletNumber += 1;
			Arsenal::Plasma* middle = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX(),getY(),getZ()-20),
							Arsenal::coord3f(0.0f, 0.0f, -400.0f));
			entities->push_back(middle);
			bulletNumber += 1;
			Arsenal::Plasma* right = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX()+5.0f, getY(), getZ()-20),
							Arsenal::coord3f(50.0f, 0.0f, -400.0f));
			entities->push_back(right);
			bulletNumber += 1;
			break;
		}

		case SPRAY5: {
			// Idea: Have the option to control angle of spray

			Arsenal::Plasma* left = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX()-5.0f, getY(), getZ()-20),
							Arsenal::coord3f(-25.0f, 0.0f, -400.0f));
			entities->push_back(left);
			bulletNumber += 1;

			Arsenal::Plasma* middle = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX(),getY(),getZ()-20),
							Arsenal::coord3f(0.0f, 0.0f, -400.0f));
			entities->push_back(middle);
			bulletNumber += 1;

			Arsenal::Plasma* right = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX()+5.0f, getY(), getZ()-20),
							Arsenal::coord3f(25.0f, 0.0f, -400.0f));
			entities->push_back(right);
			bulletNumber += 1;

			Arsenal::Plasma* top = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX(), getY()+5.0f, getZ()-20),
							Arsenal::coord3f(0.0f, 25.0f, -400.0f));
			entities->push_back(top);
			bulletNumber += 1;
			
			Arsenal::Plasma* bottom = new Arsenal::Plasma(mScene, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX(), getY()-5.0f, getZ()-20),
							Arsenal::coord3f(0.0f, -25.0f, -400.0f));
			entities->push_back(bottom);
			bulletNumber += 1;
			
			break;
		}
	}
	
}
