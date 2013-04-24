#include "Box.h"

using namespace Arsenal;

Box::Box(Ogre::SceneManager* scene, btDiscreteDynamicsWorld* dynamics,
			float xPos, float yPos)
		: Entity(dynamics, btVector3(20,20,10)) {
	// Modify bullet behaviour
	mBody->setActivationState(DISABLE_DEACTIVATION);
	mBody->setLinearFactor(btVector3(0,0,0)); // Allow no movement
	mBody->setAngularFactor(btVector3(0,0,0)); // Allow no rotations

	// Convert the ID into a string
	std::string idString = "BOX-"+getIDStr();

	mRender = scene->createEntity(idString,Ogre::SceneManager::PT_CUBE);
	mNode = scene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mRender);
	mNode->setScale(SIZE/100.0f,SIZE/100.0f,0.1f);
	mRender->setCastShadows(true);

	setPos(xPos,yPos,Z_POS);

	hp = MAX_HP;
}

Box::~Box() {
	
}

void Box::update(float delta) {
	Entity::update(delta);
	getHP();
}