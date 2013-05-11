#include "ForwardMoveBehaviour.h"

using namespace Arsenal;

ForwardMoveBehaviour::ForwardMoveBehaviour(float zSpeed) {
	mSpeed = zSpeed;
	type = FORWARD;
}

ForwardMoveBehaviour::~ForwardMoveBehaviour() {

}

void ForwardMoveBehaviour::update(float delta, Entity *e) {
	e->setVel(0,0,mSpeed);
}
