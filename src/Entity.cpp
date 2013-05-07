#include "Entity.h"
#include <iostream>

using namespace Arsenal;

Entity::Entity() {
	initID();
	mPhysics = false;
	mHP = 0;
	mDamage = 0;
	mAttack = 0;
}

Entity::Entity(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
		btVector3 hitbox, unsigned int hp, unsigned int attack, btScalar mass) {
	initID();
	mPhysics = false;
	mScene = scene;
	mHP = hp;
	mDamage = 0;
	mAttack = attack;
	initPhysics(dynamics, hitbox, mass);
}

Entity::~Entity() {
	if(mScene) {
		if(mNode) {
			mNode->detachObject(mRender);
			mScene->destroyEntity(mRender);
			mScene->destroySceneNode(mNode);
		}
	}
	if(mPhysics) {
		if(mBody!=NULL) mDynamics->removeCollisionObject(mBody);
		if(mMotion!=NULL) delete mMotion;
		if(mShape!=NULL) delete mShape;
		if(mBody!=NULL) delete mBody;
	}
}

void Entity::update(float delta) {
	// Get the bullet transform
	btTransform trans;
	mBody->getMotionState()->getWorldTransform(trans);

	// Update the Ogre scene node position
	if(mNode) {
		mNode->setPosition(
			trans.getOrigin().getX(),
			trans.getOrigin().getY(),
			trans.getOrigin().getZ());
	}
}

void Entity::initPhysics(btDiscreteDynamicsWorld* dynamics, btVector3 hitbox,
		btScalar mass) {
	if(!mPhysics) {
		mPhysics = true;

		btVector3 localInertia = btVector3(btScalar(0),btScalar(0),btScalar(0));
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(0,0,0));
		mMotion = new btDefaultMotionState(transform);
		mShape = new btBoxShape(hitbox);
		btRigidBody::btRigidBodyConstructionInfo rbInfo
			= btRigidBody::btRigidBodyConstructionInfo
				(mass,mMotion,mShape,localInertia);
		mBody = new btRigidBody(rbInfo);
		mBody->setUserPointer(this);

		mDynamics = dynamics;
		mDynamics->addRigidBody(mBody);
	} else {
		printf("Warning: Attempted to re-initialize physics for entity.\n");
	}
}

void Entity::initID() {
	// Set the ID of the entity
	static int next_id = 0;
	mID = next_id;
	next_id++;
}

std::string Entity::getIDStr() const {
	// Convert the ID into a string
	std::ostringstream oss;
	oss << mID;
	return oss.str();
}

float Entity::getX() const {
	return mBody->getCenterOfMassTransform().getOrigin().getX();
}

float Entity::getY() const {
	return mBody->getCenterOfMassTransform().getOrigin().getY();
}

float Entity::getZ() const {
	return mBody->getCenterOfMassTransform().getOrigin().getZ();
}

float Entity::getXV() const {
	return mBody->getLinearVelocity().getX();
}

float Entity::getYV() const {
	return mBody->getLinearVelocity().getY();
}

float Entity::getZV() const {
	return mBody->getLinearVelocity().getZ();
}

void Entity::setPos(float x, float y, float z) {
	// Update the bullet position
	btTransform trans = mBody->getCenterOfMassTransform();
	trans.setOrigin(btVector3(x,y,z));
	mBody->setCenterOfMassTransform(trans);

	// Update the Ogre scene node position
	mNode->setPosition(
		trans.getOrigin().getX(),
		trans.getOrigin().getY(),
		trans.getOrigin().getZ());
}

void Entity::setVel(float xv, float yv, float zv) {
	mBody->setLinearVelocity(btVector3(xv,yv,zv));
}
