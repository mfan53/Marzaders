#include "Wall.h"

using namespace Arsenal;

Wall::Wall(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
			int xcoord,int ycoord,int zcoord, std::string material,
			std::string name) {
	mShape = new btBoxShape(btVector3(initXScale,initYScale,initZScale));
	btScalar mMass = 0;
	
	btVector3 mLocalInertia = btVector3(0,0,0);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(xcoord,ycoord,zcoord));
	mMotion= new btDefaultMotionState(transform);;
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
		(mMass,mMotion,mShape,mLocalInertia);
	mBody = new btRigidBody(rbInfo);
	mBody->setRestitution(0.5);
	this->mDynamics = dynamics;

	mScene = scene;
	mRender = scene->createEntity(name, Ogre::SceneManager::PT_CUBE);
	mRender->setCastShadows(true);
	mRender->setMaterialName(material);
	mNode = scene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mNode->setPosition(Ogre::Vector3(xcoord,ycoord,zcoord));
	mNode->scale(initXScale,initYScale,initZScale);
	mNode->yaw(Ogre::Radian(-M_PI/2));

	mHP = 0;
	mAttack = 0;
	mDamage = 0;
}

Wall::~Wall() {
	
}

void Wall::setmat(std::string str) {
	mRender->setMaterialName(str);
}

