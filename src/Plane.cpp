#include "Plane.h"

using namespace Arsenal;

Plane::Plane(Ogre::SceneManager* mSceneMgr,btDiscreteDynamicsWorld* dynamicsWorld, std::string name) {
	mShape = new btBoxShape(btVector3(5,5,5));
	mMass = 10;
	isDynamic = true;
	mLocalInertia = btVector3(btScalar(0),btScalar(0),btScalar(0));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(xcoord,ycoord,zcoord));
	mMotionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
		(mMass,mMotionState,mShape,mLocalInertia);
	mBody = new btRigidBody(rbInfo);
	this->dynamicsWorld = dynamicsWorld;
	dynamicsWorld->addRigidBody(mBody);

	mBody->setRestitution(1);
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setLinearFactor(btVector3(1,1,0)); // only allow movement on x,y axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations

	mRenderEntity = mSceneMgr->createEntity(name,"RZR-002.mesh");
	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mSceneNode->attachObject(mRenderEntity);
	mRenderEntity->setCastShadows(true);
	mSceneNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
	//rotate the plane
	mSceneNode->yaw(Ogre::Radian(M_PI));
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
