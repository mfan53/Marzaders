#include "AirTraffic.h"

//#include "stdlib.h"

using namespace Arsenal;

bool insideGUI; //toggle gui menu

// Forward declarations
static void physicsTickCallback(btDynamicsWorld *world, btScalar timeStep);

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
	mWorld->setGravity(btVector3(0,0,0));
	mWorld->setInternalTickCallback(&physicsTickCallback);

	mEventQueue = EventManager::EventQueue::getEventQueue();
	mSoundManager = SoundManager::getSoundManager(10);  // 10 different sounds.
	//shootSound = mSoundManager->createSound(SND_HI_HAT);

	soundOn = true;
	insideGUI = false;
	bulletNumber = 1;
	gamePaused = true;
	insideIPMenu = false;
	mTimer = Arsenal::Timer(3,2);
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
}

//-------------------------------------------------------------------------------------
void AirTraffic::createScene(void)
{
	const char * file = (MUS_PLASMA);
	mSoundManager->loadMusic(file);
	mSoundManager->playMusic(-1);
	//mSoundManager->createSound(SND_WELCOME)->play(0);
	mSceneMgr->setSkyBox(true,"Examples/EveningSkyBox");
	//mSceneMgr->showBoundingBoxes(true);

	//load cegui stuff
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	//main menu gui
	maingui = new Arsenal::MainGUI();
	maingui->launch();

	//create the in game gui
	ingui = new Arsenal::InGUI();
	ingui->create();
}

void AirTraffic::createEntities() {
	//plane entity
	mPlane = new Arsenal::Plane(mSceneMgr,mWorld,"plane",mCamera);
	entities.push_back(mPlane);

	//land entity
	ground = new Arsenal::Wall(mSceneMgr,mWorld,0,-100,0,"Examples/GroundScroll","ground");
	ground->setmat("Examples/GroundScroll");
	entities.push_back(ground);

	// Spawn Boxes
	spawnBoxes(); 

	// Create the spawner
	mSpawner = Spawner(mSceneMgr, mWorld, &entities);
}

bool isDead (const Arsenal::Entity* value) { return value->isDead(); }

bool AirTraffic::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	bool b = BaseApplication::frameRenderingQueued(evt);
	if (!b) {
		return false;
	}

	if(gamePaused) {
		return true;
	}

	float delta = evt.timeSinceLastFrame;
	
	// Spawn enemies
	mSpawner.update(delta);

	mWorld->stepSimulation(delta,10);

	list<Arsenal::Entity*>::iterator iter = entities.begin();
	while (iter != entities.end()) {
   		(*iter)->update(delta);
		if ((*iter)->isDead()) {
			//cout << "\ndeleting shit\n" << endl;
			// printf("deleting %s; %d dmg / %d hp\n",
			// 		(*iter)->getRender()->getName().c_str(),
			// 		(*iter)->getDamage(), (*iter)->getHP());
			delete *iter;
			entities.erase(iter++);
		}
		++iter;
	}

	if(mTimer.check(delta)) {
		enemiesShoot();
	}
	
	// Update camera position
	mCamera->setPosition(Ogre::Vector3(mPlane->getX(), mPlane->getY()+20, 95));
	mCamera->lookAt(Ogre::Vector3(mPlane->getX(), mPlane->getY(),-500));

	return true;
}

void AirTraffic::enemiesShoot() {
	list<Arsenal::Entity*>::iterator iter = entities.begin();
	while (iter != entities.end()) {
		if ((*iter)->isEnemy()) {
			((Enemy*)(*iter))->shoot(bulletNumber, &entities);
		}
		++iter;
	}
}

static void physicsTickCallback(btDynamicsWorld *world, btScalar timeStep) {
    int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
	
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				Arsenal::Entity* objA = (Arsenal::Entity*) (obA->getUserPointer());
				Arsenal::Entity* objB = (Arsenal::Entity*) (obB->getUserPointer());
				if(objA != NULL && objB != NULL)
				{
					if(!objA->isDead() && !objB->isDead())
					{
						objA->damage(objB->getAttack());
						objB->damage(objA->getAttack());
					}
				}
			}
		}
	}
}

bool AirTraffic::keyPressed(const OIS::KeyEvent &arg) {
	BaseApplication::keyPressed(arg);

	//CEGUI input handling
	CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.injectKeyDown(arg.key);
	sys.injectChar(arg.text);

	if (gamePaused && arg.key != OIS::KC_P)
		return true;
	if (insideIPMenu && arg.key != OIS::KC_RETURN)
		return true;
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
		mPlane->setShot(Arsenal::SPRAY3);
	}
	else if (arg.key == OIS::KC_3) {
		mPlane->setShot(Arsenal::SPRAY5);
	}
	else if (arg.key == OIS::KC_SPACE) {
		//shootSound->play(0);
		mPlane->shoot(bulletNumber, &entities);
	}
	else if (arg.key == OIS::KC_ESCAPE) {
		mShutDown = true;
	}
	else if (arg.key == OIS::KC_P) {
		if (!insideGUI) {
			ingui->launch();
			insideGUI = true;
			pauseGame();
		}
		else {
			ingui->hide();
			insideGUI = false;
			unpauseGame();
		}
	}
	return true;
}

bool AirTraffic::keyReleased(const OIS::KeyEvent &arg) {
	BaseApplication::keyReleased(arg);

	//CEGUI input handling
	CEGUI::System::getSingleton().injectKeyUp(arg.key);	

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

void AirTraffic::spawnBoxes() {
	// Spawn Boxes
	for(float x = -100; x <= 100; x += 50) {
		for(float y = -50; y <= 150; y+= 50) {
			Arsenal::Box* mBox = new Arsenal::Box(mSceneMgr,mWorld,x,y);
			boxes.push_back(mBox);
			entities.push_back(mBox);
		}
	}
}

void AirTraffic::startGame() {
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f,1.0f,1.0f));
	gamePaused = false;
	mSoundManager->createSound(SND_WELCOME)->play(0);
	//create the entities
	createEntities();
}

void AirTraffic::quitGame() {
	mShutDown = true;
}

void AirTraffic::soundToggle() {
	if (soundOn) {
		mSoundManager->pauseMusic();
		soundOn = false;
	}
	else {
		mSoundManager->resumeMusic();
		soundOn = true;
	}
}

void AirTraffic::hideIngame() {
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f,1.0f,1.0f));
	insideGUI = false;
	gamePaused = false;
	ground->setmat("Examples/GroundScroll");
}

void AirTraffic::reset() {
	deleteEntities();
	
	maingui->show();
	insideGUI = false;
	pauseGame();
}

void AirTraffic::deleteEntities() {
	list<Arsenal::Entity*>::iterator it = entities.begin();
	while (it != entities.end()) {
		delete *it;
		entities.erase(it++);
	}	
}

void AirTraffic::pauseGame() {
	gamePaused = true;
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f,0.5f,0.5f));
	//pause plasma 
	ground->setmat("Examples/GroundStill");
	
}

void AirTraffic::unpauseGame() {
	gamePaused = false;
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f,1.0f,1.0f));
	//unpause plasma 
	ground->setmat("Examples/GroundScroll");
}

void AirTraffic::inIP() {
	insideIPMenu = true;
}

void AirTraffic::outIP() {
	insideIPMenu = false;
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
