#include "Plane.h"

using namespace Arsenal;

Plane::Plane(Ogre::SceneManager* mSceneMgr,
				btDiscreteDynamicsWorld* dynamicsWorld, std::string name) {
	//get the boudning box for the rzr-002 mesh
	
	mShape = new btBoxShape(btVector3(0,0,0));
	mMass = 10;
	isDynamic = true;
	mLocalInertia = btVector3(btScalar(0),btScalar(0),btScalar(0));
	btTransform transform;
	transform.setIdentity();
	//transform.setOrigin(btVector3(xcoord,ycoord,zcoord));
	mMotionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
		(mMass,mMotionState,mShape,mLocalInertia);
	mBody = new btRigidBody(rbInfo);
	this->dynamicsWorld = dynamicsWorld;
	dynamicsWorld->addRigidBody(mBody);

	mBody->setRestitution(1);
	mBody->setActivationState(DISABLE_DEACTIVATION);
	//mBody->setLinearFactor(btVector3(0,0,1)); // only allow movement on z axis
	//mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations

	mRenderEntity = mSceneMgr->createEntity(name,"RZR-002.mesh");
	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mSceneNode->attachObject(mRenderEntity);
	mRenderEntity->setCastShadows(true);
	mSceneNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
}

Plane::~Plane() {
	
}

void Plane::update(float delta) {
	Entity::update(delta);
}
