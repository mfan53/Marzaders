#include "SideToSideMoveBehaviour.h"
#include <iostream>

using namespace Arsenal;
using namespace std;

SideToSideMoveBehaviour::SideToSideMoveBehaviour(float zSpeed, float xSpeed, float bound) {
	mSpeed = zSpeed;
	mXSpeed = xSpeed;
	mBound = bound;
	mCalibrated = false;
	direction = (xSpeed < 0) ? 0 : 1;
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
		cout << "crossed the boundary" << endl;
		cout << "My direction is " << direction << endl;
		if (mStartX > e->getX()) {
			cout << "I am to the left of where I started " << endl;
			// The entity is to the left of where it started.
			// If you're going left, go right. Otherwise you're going right
			// and you haven't crossed over the boundary before the current update loop.
			if (direction == 0) {
				mXSpeed *= -1.0f;
				direction = 1;
				cout << "I pulled a switcharoonie" << endl;
			}
		} else {
			cout << "I am to the right of where I started" << endl;
			if (direction == 1) {
				mXSpeed *= -1.0f;
				direction = 0;
				cout << "I pulled a switcharoonie" << endl;
			}
		}
		//mXSpeed *= -1.0f;
	}

	e->setVel(mXSpeed, 0, mSpeed);
}
