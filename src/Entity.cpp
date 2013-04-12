#include "Entity.h"

using namespace Arsenal;

Entity::Entity() {
	static int next_id = 0;
	mId = next_id;
	next_id++;
	mShape = new btBoxShape(btVector3(btScalar(50),btScalar(50),btScalar(50)));
	mMass = 10;
	isDynamic = true;
	mLocalInertia = btVector3(btScalar(0),btScalar(0),btScalar(0));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(0,0,0));
	mMotionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
			(mMass,mMotionState,mShape,mLocalInertia);
	mBody = new btRigidBody(rbInfo);
}

Entity::~Entity() {
	dynamicsWorld->removeCollisionObject(mBody);
	delete mMotionState;	
	delete mShape;
	delete mBody;
}

void Entity::update(float delta) {
	btTransform trans;
	mBody->getMotionState()->getWorldTransform(trans);
	if(mSceneNode) {
		mSceneNode->setPosition(
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

void Entity::setPos(float x, float y, float z) {
	btTransform transform = mBody->getCenterOfMassTransform();
	transform.setOrigin(btVector3(x,y,z));
	mBody->setCenterOfMassTransform(transform);
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

void Entity::setVel(float xv, float yv, float zv) {
	mBody->setLinearVelocity(btVector3(xv,yv,zv));
}
