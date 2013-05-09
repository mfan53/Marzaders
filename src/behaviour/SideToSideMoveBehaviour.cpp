#include "SideToSideMoveBehaviour.h"
#include <iostream>

using namespace Arsenal;
using namespace std;

SideToSideMoveBehaviour::SideToSideMoveBehaviour(float zSpeed, float xSpeed, float bound) {
	mSpeed = zSpeed;
	mXSpeed = xSpeed;
	mBound = bound;
	mCalibrated = false;
}

SideToSideMoveBehaviour::~SideToSideMoveBehaviour() {

}

void SideToSideMoveBehaviour::update(float delta, Entity *e) {
	if (!mCalibrated) {
		mStartX = e->getStartX();
		//std::cout << "mStartX: " << mStartX << std::endl;
		mCalibrated = true;
	}

	if (fabs(mStartX - e->getX()) > mBound) {
		if (mStartX > e->getX()) {
			e->setPos(mStartX - mBound + 0.5, e->getY(), e->getZ());
			//cout << e->getIDStr() << " set xpos to " << mStartX - mBound << endl;
		} else {
			e->setPos(mStartX + mBound - 0.5, e->getY(), e->getZ());
			//cout << e->getIDStr() << " set xpos to " << mStartX + mBound << endl;
		}
		mXSpeed *= -1.0f;
	}

	e->setVel(mXSpeed, 0, mSpeed);
}
