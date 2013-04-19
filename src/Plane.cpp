#include "Plane.h"

using namespace Arsenal;

Plane::Plane(Ogre::SceneManager* mSceneMgr, btDiscreteDynamicsWorld* world,
			std::string name, Ogre::Camera* mCamera)
		: Entity(world,btVector3(5,5,5)) {
	// Modify bullet behaviour
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setRestitution(1);
	mBody->setLinearFactor(btVector3(1,1,0)); // only allow movement on x,y axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations
	// OGRE
	mRender = mSceneMgr->createEntity(name,"RZR-002.mesh");
	float boundingRadius = mRender->getMesh()->getBoundingSphereRadius();
	//TODO: Change bullet bounding box to be bounding radius
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	//mNode->attachObject(mCamera);
	mRender->setCastShadows(true);
	mNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
	//rotate the plane
	mNode->yaw(Ogre::Radian(M_PI));

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
