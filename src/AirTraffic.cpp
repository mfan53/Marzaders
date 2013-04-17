#include "AirTraffic.h"


//-------------------------------------------------------------------------------------
AirTraffic::AirTraffic(void)
{
}
//-------------------------------------------------------------------------------------
AirTraffic::~AirTraffic(void)
{
}

//-------------------------------------------------------------------------------------
void AirTraffic::createScene(void)
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f,1.0f,1.0f));

	//plane entity
	
}

bool AirTraffic::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	
}

bool AirTraffic::keyPressed(const OIS::KeyEvent &arg) {
	if (arg.key == OIS::KC_UP) {
		//TODO: Strafe plane up
	} 
	else if (arg.key == OIS::KC_DOWN) {

		//TODO: Strafe plane down
	}
	else if (arg.key == OIS::KC_RIGHT) {

		//TODO: Strafe plane right
	}
	else if (arg.key == OIS::KC_LEFT) {

		//TODO: Strafe plane left
	}
}

bool AirTraffic::keyReleased(const OIS::KeyEvent &arg) {
	if (arg.key == OIS::KC_UP || arg.key == OIS::KC_DOWN
		|| arg.key == OIS::KC_LEFT || arg.key == OIS::KC_RIGHT) {

	} 
}
