#include "Spawner.h"
#include "behaviour/SideToSideMoveBehaviour.h"
#include "Enemy.h"

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
	m_timer = Arsenal::Timer(2);
}

Spawner::~Spawner()
{
	
}

void Spawner::update(float delta)
{
	if(m_timer.check(delta)) {
		Arsenal::Enemy* enemy = new Arsenal::Enemy(m_scene, m_dynamics, 
				new Arsenal::SideToSideMoveBehaviour(100.0f, 50.0f, 50.0f),
				0, 0, Z_POS);
		m_list->push_back(enemy);
	}
}
