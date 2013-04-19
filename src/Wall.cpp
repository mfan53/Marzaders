#include "Wall.h"

using namespace Arsenal;

Wall::Wall(Ogre::SceneManager* mSceneMgr,
				btDiscreteDynamicsWorld* dynamicsWorld,int xcoord,int zcoord, std::string material, std::string name) {
	if (xcoord == maxXCoord || xcoord == minXCoord)
		mShape = new btBoxShape(btVector3(0,initYScale*100,1.8f));
	else
		mShape = new btBoxShape(
					btVector3(initXScale*100,initYScale*100,initZScale*100));
	mMass = 0;
	isDynamic = false;
	mLocalInertia = btVector3(0,0,0);
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(xcoord,initYPos,zcoord));
	mMotionState = new btDefaultMotionState(transform);;
	btRigidBody::btRigidBodyConstructionInfo rbInfo
		= btRigidBody::btRigidBodyConstructionInfo
		(mMass,mMotionState,mShape,mLocalInertia);
	mBody = new btRigidBody(rbInfo);
	this->dynamicsWorld = dynamicsWorld;
	if(!((xcoord == maxXCoord && zcoord == wallZCoord)
		|| (xcoord == minXCoord && zcoord == wallZCoord))) {
		dynamicsWorld->addRigidBody(mBody);
	}

	mBody->setRestitution(0.5);
	mRenderEntity = mSceneMgr->createEntity(name, Ogre::SceneManager::PT_CUBE);
	mRenderEntity->setCastShadows(true);
	mRenderEntity->setMaterialName(material);
	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mSceneNode->attachObject(mRenderEntity);
	mSceneNode->setPosition(Ogre::Vector3(xcoord,initYPos,zcoord));
	if (xcoord == maxXCoord || xcoord == minXCoord)
		mSceneNode->scale(0,initYScale,1.8f);
	else
		mSceneNode->scale(initXScale,initYScale,initZScale);
}

Wall::~Wall() {
	
}

