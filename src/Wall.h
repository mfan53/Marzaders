#ifndef INC_ARSENAL_WALL_H
#define INC_ARSENAL_WALL_H

#include "Entity.h"

namespace Arsenal {
	class Wall : public Entity {
	public:
		Wall(Ogre::SceneManager* mSceneMgr,btDiscreteDynamicsWorld* dynamicsWorld,int xcoord,int ycoord,int zcoord, std::string material, 			std::string name);
		virtual ~Wall();
		void setmat(std::string str);

	private:
		const static float initXScale = 100;
		const static float initYScale = 0;
		const static float initZScale = 100;
	};
}

#endif // INC_ARSENAL_WALL_H
