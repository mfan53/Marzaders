#ifndef INC_ARSENAL_WALL_H
#define INC_ARSENAL_WALL_H

#include "Entity.h"

namespace Arsenal {
	class Wall : public Entity {
	public:
		Wall(Ogre::SceneManager* mSceneMgr,btDiscreteDynamicsWorld* dynamicsWorld,int xcoord,int zcoord, std::string material, std::string 			name);
		virtual ~Wall();

	private:
		const static float initYPos = 10;
		const static float initXScale = 1.7f;
		const static float initYScale = .2f;
		const static float initZScale = 0;
		const static float maxXCoord = 170;
		const static float minXCoord = -170;
		const static float wallZCoord = 0;
	};
}

#endif // INC_ARSENAL_WALL_H
