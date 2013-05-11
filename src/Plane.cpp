#include "Plane.h"
#include "Globals.h"

using namespace Arsenal;
using namespace std;

Plane::Plane(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics)
		: Entity(scene, HP, ATK) {
	// OGRE
	mRender = mScene->createEntity("plane","RZR-002.mesh");
	mRender->setCastShadows(true);
	mNode = mScene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
	mNode->yaw(Ogre::Radian(M_PI)); //rotate the plane

	// Setup bullet
	float bounds = mRender->getMesh()->getBoundingSphereRadius();
	initPhysics(dynamics, btVector3(bounds,bounds,bounds), COL_SHIP, COL_ENEMY | COL_BULLET);
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setRestitution(1);
	mBody->setLinearFactor(btVector3(1,1,0)); // only allow movement on x,y axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations

	mMoveUp = false;
	mMoveDown = false;
	mMoveLeft = false;
	mMoveRight = false;

	shootSound = SoundManager::getSoundManager()->createSound(SND_BULLET);
	shot_type = SINGLE;

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

	// Prevent the player from moving further out of bounds
	x = (getX() < -100 && x < 0) || (getX() > 100 && x > 0) ? 0 : x;
	y = (getY() < -50 && y < 0) || (getY() > 150 && y > 0) ? 0 : y;

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

void Plane::reset() {
	btTransform transform = mBody->getCenterOfMassTransform();
	transform.setOrigin(btVector3(xcoord,ycoord,zcoord));
	mBody->setCenterOfMassTransform(transform);
}

void Plane::shoot(std::list<Arsenal::Entity*>* entities) {
	std::stringstream ss;
	string name;
	shootSound->play(0);

	switch (shot_type) {

		case SINGLE: {
			Arsenal::Plasma* p = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX(),getY(),getZ()-20),
							Arsenal::coord3f(0.0f, 0.0f, -400.0f));
			entities->push_back(p);
			break;
		}

		case SPRAY3: {
			// Idea: Have the option to control angle of spray

			Arsenal::Plasma* left = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX()-5.0f, getY(), getZ()-20),
							Arsenal::coord3f(-50.0f, 0.0f, -400.0f));
			entities->push_back(left);
			
			Arsenal::Plasma* middle = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX(),getY(),getZ()-20),
							Arsenal::coord3f(0.0f, 0.0f, -400.0f));
			entities->push_back(middle);
			
			Arsenal::Plasma* right = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX()+5.0f, getY(), getZ()-20),
							Arsenal::coord3f(50.0f, 0.0f, -400.0f));
			entities->push_back(right);

			break;
		}

		case SPRAY5: {
			// Idea: Have the option to control angle of spray

			Arsenal::Plasma* left = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX()-5.0f, getY(), getZ()-20),
							Arsenal::coord3f(-25.0f, 0.0f, -400.0f));
			entities->push_back(left);

			Arsenal::Plasma* middle = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX(),getY(),getZ()-20),
							Arsenal::coord3f(0.0f, 0.0f, -400.0f));
			entities->push_back(middle);

			Arsenal::Plasma* right = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX()+5.0f, getY(), getZ()-20),
							Arsenal::coord3f(25.0f, 0.0f, -400.0f));
			entities->push_back(right);

			Arsenal::Plasma* top = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX(), getY()+5.0f, getZ()-20),
							Arsenal::coord3f(0.0f, 25.0f, -400.0f));
			entities->push_back(top);
			
			Arsenal::Plasma* bottom = new Arsenal::Plasma(mScene, mDynamics,
							Arsenal::coord3f(getX(), getY()-5.0f, getZ()-20),
							Arsenal::coord3f(0.0f, -25.0f, -400.0f));
			entities->push_back(bottom);

			break;
		}
	}
	
}
