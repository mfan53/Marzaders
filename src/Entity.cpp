#include "Entity.h"

using namespace Arsenal;

Entity::Entity() {
	// Set the ID of the entity
	static int next_id = 0;
	m_id = next_id;
	next_id++;

	// Create the physics components of the entity
	btScalar mass = 10;
	btVector3 localInertia = btVector3(btScalar(0),btScalar(0),btScalar(0));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(0,0,0));
	m_motion = new btDefaultMotionState(transform);
	m_shape = new btBoxShape(btVector3(btScalar(50),btScalar(50),btScalar(50)));
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
			(mass,m_motion,m_shape,localInertia);
	m_body = new btRigidBody(rbInfo);
}

Entity::~Entity() {
	m_dynamics->removeCollisionObject(m_body);
	delete m_motion;
	delete m_shape;
	delete m_body;
}

void Entity::update(float delta) {
	// Get the bullet transform
	btTransform trans;
	m_body->getMotionState()->getWorldTransform(trans);

	// Update the Ogre scene node position
	if(m_node) {
		m_node->setPosition(
			trans.getOrigin().getX(),
			trans.getOrigin().getY(),
			trans.getOrigin().getZ());
	}
}

float Entity::getX() {
	return m_body->getCenterOfMassTransform().getOrigin().getX();
}

float Entity::getY() {
	return m_body->getCenterOfMassTransform().getOrigin().getY();
}

float Entity::getZ() {
	return m_body->getCenterOfMassTransform().getOrigin().getZ();
}

float Entity::getXV() {
	return m_body->getLinearVelocity().getX();
}

float Entity::getYV() {
	return m_body->getLinearVelocity().getY();
}

float Entity::getZV() {
	return m_body->getLinearVelocity().getZ();
}

void Entity::setPos(float x, float y, float z) {
	// Update the bullet position
	btTransform trans = m_body->getCenterOfMassTransform();
	trans.setOrigin(btVector3(x,y,z));
	m_body->setCenterOfMassTransform(trans);

	// Update the Ogre scene node position
	m_node->setPosition(
		trans.getOrigin().getX(),
		trans.getOrigin().getY(),
		trans.getOrigin().getZ());
}

void Entity::setVel(float xv, float yv, float zv) {
	m_body->setLinearVelocity(btVector3(xv,yv,zv));
}
