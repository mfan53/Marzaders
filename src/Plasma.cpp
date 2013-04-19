#include "Plasma.h"

using namespace Arsenal;

Plasma::Plasma(Ogre::SceneManager* mSceneMgr, btDiscreteDynamicsWorld* dynamicsWorld,
				std::string name, const float x, const float y, const float z) {
	// OGRE
	mRender = mSceneMgr->createEntity(name,"geosphere8000.mesh");
	float boundingRadius = mRender->getMesh()->getBoundingSphereRadius();
	mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mRender->setCastShadows(true);
	mRender->setMaterialName("Examples/SphereMappedDroplet");
	mNode->scale(0.008,0.008,0.01);
	mNode->setPosition(Ogre::Vector3(x, y,z));

	// Bullet
	mShape = new btBoxShape(btVector3(boundingRadius,boundingRadius,boundingRadius));
	btScalar mass = 10;
	btVector3 localInertia = btVector3(btScalar(0),btScalar(0),btScalar(0));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(x,y,z));
	mMotion = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
		(mass,mMotion,mShape,localInertia);
	mBody = new btRigidBody(rbInfo);
	this->mDynamics = dynamicsWorld;
	mDynamics->addRigidBody(mBody);

	mBody->setRestitution(1);
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setLinearFactor(btVector3(0, 0, 1)); // only allow movement on z axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations
}

Plasma::~Plasma() {
	
}

void Plasma::update(float delta) {
	mBody->setLinearVelocity(btVector3(0, 0, -200.0f));
	Entity::update(delta);
}