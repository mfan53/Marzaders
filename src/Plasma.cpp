#include "Globals.h"
#include "Plasma.h"

using namespace Arsenal;
using namespace std;

Ogre::ParticleSystem* particle1;

Plasma::Plasma(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
				const coord3f pos, const coord3f vel, bool isEnemyShot)
			: Entity(scene, HP, ATK) {
	// OGRE
	if (isEnemyShot) {
		mRender = scene->createEntity("bullet-"+getIDStr(), Ogre::SceneManager::PT_SPHERE);
	} else {
		mRender = scene->createEntity("plasma-"+getIDStr(), Ogre::SceneManager::PT_SPHERE);
	}
	mNode = scene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mRender->setCastShadows(true);

	float scaleFactor = 0.0f;
	if (isEnemyShot) {
		mRender->setMaterialName("Color/Red");
		scaleFactor = 0.03f;
	} else {
		mRender->setMaterialName("Examples/SphereMappedDroplet");
		scaleFactor = 0.04f;
		//particle trail for plasma
		//std::string plasmaID = "plasma-" + getIDStr();
		//particle1 = scene->createParticleSystem(plasmaID,"Examples/ParticleTrail");
		//particle1->setVisible(true);
		//mNode->attachObject(particle1);
	}
	
	mNode->scale(scaleFactor, scaleFactor, scaleFactor * 10);
	Ogre::Vector3 hitbox = scaleFactor * mRender->getBoundingBox().getMaximum();

	// Bullet
	int coll = isEnemyShot ? COL_BULLET : COL_PLASMA;
	int collW = isEnemyShot ? COL_PLASMA | COL_SHIP | COL_BOX : COL_BULLET | COL_ENEMY;
	initPhysics(dynamics, btVector3(hitbox.x, hitbox.y, hitbox.z), coll, collW,
		10, pos.x, pos.y, pos.z);

	mBody->setRestitution(0);
	mBody->setLinearVelocity(btVector3(vel.x, vel.y, vel.z));

	m_isEnemyShot = isEnemyShot;

	
}

Plasma::~Plasma() {
	
}

void Plasma::update(float delta) {
	Entity::update(delta);

	// Remove the bullet if it is out of range
	if(getZ() > Globals::WORLD_END || getZ() < Globals::WORLD_START) {
		damage(mHP);
	}

	// Remove the bullet if it is moving in the wrong direction
	if(m_isEnemyShot == getZV() < 0) {
		damage(mHP);
	}
}
