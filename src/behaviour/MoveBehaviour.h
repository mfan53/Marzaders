#ifndef INC_ARSENAL_BEHAVIOUR_MOVEBEHAVIOUR_H
#define INC_ARSENAL_BEHAVIOUR_MOVEBEHAVIOUR_H

#include "../Entity.h"

namespace Arsenal {
	enum movementType {
		FORWARD = 1,
		SHIFTER = 2
	};
	class MoveBehaviour {
	public:
		movementType type;
		virtual void update(float delta, Entity *e) = 0;
	};
}

#endif // INC_ARSENAL_BEHAVIOUR_MOVEBEHAVIOUR_H
