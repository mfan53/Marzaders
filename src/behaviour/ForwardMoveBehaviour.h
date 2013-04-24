#ifndef INC_ARSENAL_BEHAVIOUR_FORWARDMOVEBEHAVIOUR_H
#define INC_ARSENAL_BEHAVIOUR_FORWARDMOVEBEHAVIOUR_H

#include "MoveBehaviour.h"

namespace Arsenal {
	class ForwardMoveBehaviour : public MoveBehaviour {
	public:
		ForwardMoveBehaviour(float zSpeed);
		virtual ~ForwardMoveBehaviour();

		void update(float delta, Entity *e);

	private:
		float mSpeed;
	};
}

#endif // INC_ARSENAL_BEHAVIOUR_FORWARDMOVEBEHAVIOUR_H
