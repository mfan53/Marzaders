#include "Plane.h"

using namespace Arsenal;
using namespace std;

Plane::Plane(Ogre::SceneManager* mSceneMgr, btDiscreteDynamicsWorld* world,
			std::string name, Ogre::Camera* mCamera) {
	sceneManager = mSceneMgr;
	dynWorld = world;
	shot_type = SINGLE;

	// OGRE
	mRender = mSceneMgr->createEntity(name,"RZR-002.mesh");
	float bounds = mRender->getMesh()->getBoundingSphereRadius();
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	//mNode->attachObject(mCamera);
	mRender->setCastShadows(true);
	mNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
	//rotate the plane
	mNode->yaw(Ogre::Radian(M_PI));

	// Setup bullet
	initPhysics(world, btVector3(bounds,bounds,bounds));
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setRestitution(1);
	mBody->setLinearFactor(btVector3(1,1,0)); // only allow movement on x,y axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations

	mMoveUp = false;
	mMoveDown = false;
	mMoveLeft = false;
	mMoveRight = false;
}

Plane::~Plane() {
	
}

void Plane::update(float delta) {
	float y = 0;
	float x = 0;
	if (mMoveUp) {
		y += 50;
	}
	if (mMoveDown) {
		y -= 50;
	}
	if (mMoveLeft) {
		x -= 50;
	}
	if (mMoveRight) {
		x += 50;
	}
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

void Plane::shoot(int& bulletNumber, std::list<Arsenal::Entity*> * entities) {
	std::stringstream ss;
	string name;

	if (bulletNumber >= 9999) bulletNumber = 0;

	switch (shot_type) {

		case SINGLE: {
			Arsenal::Plasma* p = new Arsenal::Plasma(sceneManager, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX(),getY(),getZ()-20),
							Arsenal::coord3f(0.0f, 0.0f, -400.0f));
			entities->push_back(p);
			bulletNumber += 1;
			break;
		}
		case SPRAY3: {
			// Idea: Have the option to control angle of spray

			Arsenal::Plasma* left = new Arsenal::Plasma(sceneManager, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX()-5.0f, getY(), getZ()-20),
							Arsenal::coord3f(-50.0f, 0.0f, -400.0f));
			entities->push_back(left);
			bulletNumber += 1;
			Arsenal::Plasma* middle = new Arsenal::Plasma(sceneManager, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX(),getY(),getZ()-20),
							Arsenal::coord3f(0.0f, 0.0f, -400.0f));
			entities->push_back(middle);
			bulletNumber += 1;
			Arsenal::Plasma* right = new Arsenal::Plasma(sceneManager, dynWorld, intToString(bulletNumber),
							Arsenal::coord3f(getX()+5.0f, getY(), getZ()-20),
							Arsenal::coord3f(50.0f, 0.0f, -400.0f));
			entities->push_back(right);
			bulletNumber += 1;
			break;
		}
	}
	
}
