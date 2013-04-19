#include "Entity.h"

using namespace Arsenal;

Entity::Entity() {
	// Set the ID of the entity
	static int next_id = 0;
	mID = next_id;
	next_id++;

	// Create the physics components of the entity
	btScalar mass = 10;
	btVector3 localInertia = btVector3(btScalar(0),btScalar(0),btScalar(0));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(0,0,0));
	mMotion = new btDefaultMotionState(transform);
	mShape = new btBoxShape(btVector3(btScalar(50),btScalar(50),btScalar(50)));
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
			(mass,mMotion,mShape,localInertia);
	mBody = new btRigidBody(rbInfo);
}

Entity::~Entity() {
	mDynamics->removeCollisionObject(mBody);
	delete mMotion;
	delete mShape;
	delete mBody;
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

float Entity::getX() {
	return mBody->getCenterOfMassTransform().getOrigin().getX();
}

float Entity::getY() {
	return mBody->getCenterOfMassTransform().getOrigin().getY();
}

float Entity::getZ() {
	return mBody->getCenterOfMassTransform().getOrigin().getZ();
}

float Entity::getXV() {
	return mBody->getLinearVelocity().getX();
}

float Entity::getYV() {
	return mBody->getLinearVelocity().getY();
}

float Entity::getZV() {
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
