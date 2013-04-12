#ifndef INC_EVENTMANAGER_EVENTQUEUE_H
#define INC_EVENTMANAGER_EVENTQUEUE_H

#include <list>
#include "Event.h"

namespace EventManager {
	class EventQueue {
		public:
			static EventQueue * getEventQueue();

			Event * getNext();
			void add(Event * e);
			bool hasNext();
			int getSize() {return size;}
		protected:
			EventQueue();
			~EventQueue();
			std::list<Event*> events;
			int size;

		private:
			static bool created;
			static EventQueue * queue;
	};
}

#endif //  INC_EVENTMANAGER_EVENTQUEUE_H
