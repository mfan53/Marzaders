#include "Plane.h"

using namespace Arsenal;

Plane::Plane(Ogre::SceneManager* mSceneMgr,btDiscreteDynamicsWorld* dynamicsWorld, std::string name) {
	mShape = new btBoxShape(btVector3(5,5,5));
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

	mRender = mSceneMgr->createEntity(name,"RZR-002.mesh");
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mRender->setCastShadows(true);
	mNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
	//rotate the plane
	mNode->yaw(Ogre::Radian(M_PI));
}

Plane::~Plane() {
	
}

void Plane::update(float delta) {
	if (!mMoveUp && !mMoveDown && !mMoveLeft && !mMoveRight) {
		stop();
	}
	else if (mMoveUp) {
		mBody->setLinearVelocity(btVector3(0.0f, 50.0f, 0.0f));
	}
	else if (mMoveDown) {
		mBody->setLinearVelocity(btVector3(0.0f, -50.0f, 0.0f));
	}
	else if (mMoveLeft) {
		mBody->setLinearVelocity(btVector3(-50.0f, 0.0f, 0.0f));
	}
	else if (mMoveRight) {
		mBody->setLinearVelocity(btVector3(50.0f, 0.0f, 0.0f));
	}

	Entity::update(delta);
}

void Plane::moveUp() {
	mMoveUp = true;
	mMoveDown = false;
	mMoveLeft = false;
	mMoveRight = false;
}

void Plane::moveDown() {
	mMoveUp = false;
	mMoveDown = true;
	mMoveLeft = false;
	mMoveRight = false;
}

void Plane::moveLeft() {
	mMoveUp = false;
	mMoveDown = false;
	mMoveLeft = true;
	mMoveRight = false;
}

void Plane::moveRight() {
	mMoveUp = false;
	mMoveDown = false;
	mMoveLeft = false;
	mMoveRight = true;
}

void Plane::stop() {
	mMoveUp = false;
	mMoveDown = false;
	mMoveLeft = false;
	mMoveRight = false;
	mBody->setLinearVelocity(btVector3(0.0f,0.0f,0.0f));
}
