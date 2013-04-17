#ifndef __AirTraffic_h_
#define __AirTraffic_h_

#include <vector>
#include <iostream>
#include <OgreManualObject.h>
#include <stdlib.h> 
#include <string.h>
#include "BaseApplication.h"
#include "btBulletDynamicsCommon.h"
#include "Entity.h"
#include "sound/SoundManager.h"
#include "ScoreManager.h"
#include "event/Event.h"
#include "event/EventManager.h"
#include "net/Endpoint.h"
#include "net/Host.h"
#include "net/Socket.h"
#include "Wall.h"
#include "Plane.h"
#include <math.h>

class AirTraffic : public BaseApplication
{
public:
   	AirTraffic(void);
   	virtual ~AirTraffic(void);

	//bool keyPressed(const OIS::KeyEvent &arg);
   	//bool keyReleased(const OIS::KeyEvent &arg);
 
protected:
   	virtual void createScene(void);
	//virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

#endif // #ifndef __AirTraffic_h_
