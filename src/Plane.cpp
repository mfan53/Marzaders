#include "Plane.h"

using namespace Arsenal;

Plane::Plane(Ogre::SceneManager* mSceneMgr,btDiscreteDynamicsWorld* dynamicsWorld, std::string name, Ogre::Camera* mCamera) {
	// OGRE
	mRender = mSceneMgr->createEntity(name,"RZR-002.mesh");
	float boundingRadius = mRender->getMesh()-getBoundingSphereRadius();
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	//mNode->attachObject(mCamera);
	mRender->setCastShadows(true);
	mNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
	//rotate the plane
	mNode->yaw(Ogre::Radian(M_PI));

	// Bullet
	mShape = new btBoxShape(btVector3(boundingRadius,boundingRadius,boundingRadius));
	btScalar mass = 10;
	btVector3 localInertia = btVector3(btScalar(0),btScalar(0),btScalar(0));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(xcoord,ycoord,zcoord));
	mMotion = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
		(mass,mMotion,mShape,localInertia);
	mBody = new btRigidBody(rbInfo);
	this->mDynamics = dynamicsWorld;
	mDynamics->addRigidBody(mBody);

	mBody->setRestitution(1);
	mBody->setActivationState(DISABLE_DEACTIVATION);
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

void Plane::moveUp() {
	mMoveUp = true;
}

void Plane::moveDown() {
	mMoveDown = true;
}

void Plane::moveLeft() {
	mMoveLeft = true;
}

void Plane::moveRight() {
	mMoveRight = true;
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
