#ifndef INC_ARSENAL_BEHAVIOUR_SIDETOSIDEMOVEBEHAVIOUR_H
#define INC_ARSENAL_BEHAVIOUR_SIDETOSIDEMOVEBEHAVIOUR_H

#include "MoveBehaviour.h"
#include <math.h>

namespace Arsenal {
	class SideToSideMoveBehaviour : public MoveBehaviour {
	public:
		SideToSideMoveBehaviour(float zSpeed, float xSpeed, float bound);
		virtual ~SideToSideMoveBehaviour();

		void update(float delta, Entity *e);

	private:
		float mSpeed;
		float mXSpeed;
		float mBound;
		float mStartX;
		bool mCalibrated;

		// 0:left, 1:right
		int direction;
	};
}

#endif // INC_ARSENAL_BEHAVIOUR_SIDETOSIDEMOVEBEHAVIOUR_H
