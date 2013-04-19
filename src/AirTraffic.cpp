#include "AirTraffic.h"


//-------------------------------------------------------------------------------------
AirTraffic::AirTraffic(void)
{
	// Initialize bullet
	mCollisionConfig = new btDefaultCollisionConfiguration();
	mDispatcher = new btCollisionDispatcher(mCollisionConfig);
	mOverlappingPairCache = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver;
	mWorld = new btDiscreteDynamicsWorld
		(mDispatcher,mOverlappingPairCache,mSolver,mCollisionConfig);

	//mWorld->setGravity(btVector3(0,-9.8,0));
	mWorld->setGravity(btVector3(0,0,0));
	mEventQueue = EventManager::EventQueue::getEventQueue();
}
//-------------------------------------------------------------------------------------
AirTraffic::~AirTraffic(void)
{
	for (std::list<Arsenal::Entity*>::iterator iter = entities.begin();
			iter != entities.end(); iter++)
	{
		delete *iter;
	}
	entities.clear();
	delete mWorld;
	delete mSolver;
	delete mOverlappingPairCache;
	delete mDispatcher;
	delete mCollisionConfig;
	//delete &mSoundManager;
}

//-------------------------------------------------------------------------------------
void AirTraffic::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f,1.0f,1.0f));

	//plane entity
	mPlane = new Arsenal::Plane(mSceneMgr,mWorld,"plane",mCamera);
	entities.push_back(mPlane);
	
	mSceneMgr->setSkyBox(true,"Examples/EveningSkyBox");
}

bool AirTraffic::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	bool b = BaseApplication::frameRenderingQueued(evt);
	if (!b) {
		return false;
	}

	float delta = evt.timeSinceLastFrame;
	
	mWorld->stepSimulation(delta,10);
	
	for(std::list<Arsenal::Entity*>::iterator iter = entities.begin();
		iter != entities.end(); ++iter) {
   		(*iter)->update(delta);
	}

	return true;
}

bool AirTraffic::keyPressed(const OIS::KeyEvent &arg) {
	BaseApplication::keyPressed(arg);
	if (arg.key == OIS::KC_W) {
		mPlane->moveUp();
	} 
	else if (arg.key == OIS::KC_S) {
		mPlane->moveDown();
	}
	else if (arg.key == OIS::KC_D) {
		mPlane->moveRight();
	}
	else if (arg.key == OIS::KC_A) {
		mPlane->moveLeft();
	}
	else if (arg.key == OIS::KC_SPACE) {
		//Arsenal::Plasma* p = new Arsenal::Plasma(mSceneMgr, mWorld, "p", 0, 0, -1);
		//entities.push_back(p);
	}
	return true;
}

bool AirTraffic::keyReleased(const OIS::KeyEvent &arg) {
	BaseApplication::keyReleased(arg);
	switch (arg.key) {
		case OIS::KC_W :
			mPlane->stop(Arsenal::UP);
			break; 
		case OIS::KC_S :
			mPlane->stop(Arsenal::DOWN);
			break; 
		case OIS::KC_A :
			mPlane->stop(Arsenal::LEFT);
			break; 
		case OIS::KC_D :
			mPlane->stop(Arsenal::RIGHT);
			break;
	} 
	return true;
}
