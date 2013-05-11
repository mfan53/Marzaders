#ifndef INC_AIRTRAFFIC_h
#define INC_AIRTRAFFIC_h

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <OgreManualObject.h>
#include "BaseApplication.h"
#include "Box.h"
#include "Enemy.h"
#include "Entity.h"
#include "InGUI.h"
#include "MainGUI.h"
#include "Plane.h"
#include "Plasma.h"
#include "ScoreManager.h"
#include "Spawner.h"
#include "Wall.h"
#include "behaviour/ForwardMoveBehaviour.h"
#include "behaviour/SideToSideMoveBehaviour.h"
#include "btBulletDynamicsCommon.h"
#include "event/Event.h"
#include "event/EventManager.h"
#include "net/Endpoint.h"
#include "net/Host.h"
#include "net/Socket.h"
#include "sound/SoundManager.h"
#include "Timer.h"

class AirTraffic : public BaseApplication
{
public:
   	AirTraffic(void);
   	virtual ~AirTraffic(void);

	bool keyPressed(const OIS::KeyEvent &arg);
   	bool keyReleased(const OIS::KeyEvent &arg);
	void quitGame();
	void startGame();
	void pauseGame();
	void unpauseGame();
	void reset();
	void soundToggle();
	void hideIngame();
	void inIP();
	void outIP();
	bool mouseMoved( const OIS::MouseEvent &arg);
	bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	unsigned int getScore() { return mScore; };
	unsigned int increaseScore(unsigned int points)
		{ mScore += points; return mScore; };
	unsigned int decreaseScore(unsigned int points)
		{ mScore = points > mScore ? 0 : mScore - points; return mScore; };

protected:
   	virtual void createScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void removeOutOfBoundsBullets();
	void spawnBoxes();
	void createEntities();
	void deleteEntities();
	void enemiesShoot();

	Arsenal::Spawner mSpawner;
	std::list<Arsenal::Entity*> entities;
	std::list<Arsenal::Box*> boxes;
	Arsenal::Plane *mPlane;
	Arsenal::Wall *ground;
	int bulletNumber;
	Arsenal::Timer mTimer;
	Arsenal::Timer mScoreTimer;
	
	btDefaultCollisionConfiguration* mCollisionConfig;
	btCollisionDispatcher* mDispatcher;
	btBroadphaseInterface* mOverlappingPairCache;
	btSequentialImpulseConstraintSolver* mSolver;
	btDiscreteDynamicsWorld* mWorld;
	EventManager::EventQueue * mEventQueue;
	Arsenal::SoundManager * mSoundManager;
	Sound * shootSound;

	bool soundOn;
	Arsenal::InGUI* ingui;
	Arsenal::MainGUI* maingui;
	bool gamePaused;
	bool insideIPMenu;

private:
	unsigned int mScore;

};

#endif // #ifndef _AIRTRAFFIC_h
