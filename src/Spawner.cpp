#include "Spawner.h"
#include <iostream>

using namespace std;
using namespace Arsenal;

Spawner::Spawner()
{
}

Spawner::Spawner(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
				 std::list<Arsenal::Entity*>* entities)
{
	m_scene = scene;
	m_dynamics = dynamics;
	m_list = entities;
	m_timer = Arsenal::Timer(10,10);
	currentMovement = FORWARD;
	zSpeed = 25.0f;
	m_list = entities;
}

Spawner::~Spawner()
{
	
}

void Spawner::update(float delta)
{
	if(m_timer.check(delta)) {
		spawnEnemyGrid(5, 5, 50.0f, 50.0f);
	}
}

void Spawner::spawnEnemyGrid(int numRows, int numCols, float rowSpacing, float colSpacing) {
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			switch (currentMovement) {
				case FORWARD : {
					// cout << "Spawning forwards" << endl;
					Arsenal::Enemy* enemy = new Arsenal::Enemy(m_scene, m_dynamics, 
						new Arsenal::ForwardMoveBehaviour(zSpeed), gridStartX + (c * colSpacing), 
						gridStartY + (r * rowSpacing), Z_POS);
					m_list->push_back(enemy);
					break;
				}

				case SHIFTER : {
					// cout << "Spawning shifters" << endl;
					Arsenal::Enemy* enemy = new Arsenal::Enemy(m_scene, m_dynamics, 
						new Arsenal::SideToSideMoveBehaviour(zSpeed, 50.0f, 50.0f),
						gridStartX + (c * colSpacing), gridStartY + (r * rowSpacing), Z_POS);
					m_list->push_back(enemy);
					break;
				}
			}
		}
	}
	if (currentMovement == FORWARD) currentMovement = SHIFTER;
	else currentMovement = FORWARD;
}

