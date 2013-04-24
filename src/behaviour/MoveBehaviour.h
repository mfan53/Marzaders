#ifndef INC_ARSENAL_BEHAVIOUR_MOVEBEHAVIOUR_H
#define INC_ARSENAL_BEHAVIOUR_MOVEBEHAVIOUR_H

#include "../Entity.h"

namespace Arsenal {
	class MoveBehaviour {
	public:
		virtual void update(float delta, Entity *e) = 0;
	};
}

#endif // INC_ARSENAL_BEHAVIOUR_MOVEBEHAVIOUR_H
