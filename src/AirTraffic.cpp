#include "AirTraffic.h"

//#include "stdlib.h"

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

	soundOn = true;
	bulletNumber = 1;
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
	mSceneMgr->setSkyBox(true,"Examples/EveningSkyBox");

	//plane entity
	mPlane = new Arsenal::Plane(mSceneMgr,mWorld,"plane",mCamera);
	entities.push_back(mPlane);

	//space sky plane
	entities.push_back(new Arsenal::Wall(mSceneMgr,mWorld,0,-100,0,"Examples/Ground","back wall"));

	// Spawn Boxes
	for(float x = -100; x <= 100; x += 25) {
		for(float y = -100; y <= 100; y+= 25) {
			Arsenal::Box* mBox = new Arsenal::Box(mSceneMgr,mWorld,x,y);
			boxes.push_back(mBox);
			entities.push_back(mBox);
		}
	}

	// Spawn Enemies
	Arsenal::Enemy* enemy = new Arsenal::Enemy(mSceneMgr, mWorld, new Arsenal::ForwardMoveBehaviour(300));
	entities.push_back(enemy);

	//load cegui stuff
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	//main menu gui
	Arsenal::MainGUI* maingui = new Arsenal::MainGUI();
	maingui->launch();
}

bool AirTraffic::outOfBounds (const Arsenal::Entity* value) {
	return value->getZ() <= WORLD_END;
}

bool AirTraffic::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	bool b = BaseApplication::frameRenderingQueued(evt);
	if (!b) {
		return false;
	}

	//entities.remove_if (outOfBounds);

	float delta = evt.timeSinceLastFrame;
	
	mWorld->stepSimulation(delta,10);
	
	for(std::list<Arsenal::Entity*>::iterator iter = entities.begin();
		iter != entities.end(); ++iter) {
   		(*iter)->update(delta);
	}

	// Update camera position
	mCamera->setPosition(Ogre::Vector3(mPlane->getX(), mPlane->getY()+20, 95));
	mCamera->lookAt(Ogre::Vector3(mPlane->getX(), mPlane->getY(),-500));

	return true;
}

bool AirTraffic::keyPressed(const OIS::KeyEvent &arg) {
	BaseApplication::keyPressed(arg);
	if (arg.key == OIS::KC_W) {
		mPlane->move(Arsenal::UP);
	} 
	else if (arg.key == OIS::KC_S) {
		mPlane->move(Arsenal::DOWN);
	}
	else if (arg.key == OIS::KC_D) {
		mPlane->move(Arsenal::RIGHT);
	}
	else if (arg.key == OIS::KC_A) {
		mPlane->move(Arsenal::LEFT);
	}
	else if (arg.key == OIS::KC_1) {
		mPlane->setShot(Arsenal::SINGLE);
	}
	else if (arg.key == OIS::KC_2) {
		mPlane->setShot(Arsenal::CROSS);
	}
	else if (arg.key == OIS::KC_SPACE) {
		mPlane->shoot(bulletNumber, &entities);
		// stringstream ss; 
		// ss << bulletNumber;
		// string name = ss.str();
		// bulletNumber += 1;
		// if (bulletNumber >= 9999)
		// 	bulletNumber = 0;
		// Arsenal::Plasma* p = new Arsenal::Plasma(mSceneMgr, mWorld, name,
		// 		mPlane->getX(), mPlane->getY(), mPlane->getZ()-20);
		// entities.push_back(p);
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

void AirTraffic::quitGame() {
	mShutDown = true;
}

void AirTraffic::soundToggle() {
	if (soundOn) {
		//mSoundManager.pauseMusic();
		soundOn = false;
	}
	else {
		//mSoundManager.resumeMusic();
		soundOn = true;
	}
}

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID) {
	switch(buttonID) {
		case OIS::MB_Left:
       			return CEGUI::LeftButton;
 		case OIS::MB_Right:
        		return CEGUI::RightButton;
 		case OIS::MB_Middle:
        		return CEGUI::MiddleButton;
 		default:
        		return CEGUI::LeftButton;
	}
}

bool AirTraffic::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
	return true;
}

bool AirTraffic::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
	return true;
}

bool AirTraffic::mouseMoved( const OIS::MouseEvent &arg )
{
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	// Scroll wheel.
	if (arg.state.Z.rel)
    		sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	return true;
}
