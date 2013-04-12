#include "EventQueue.h"

namespace EventManager {
	bool EventQueue::created = false;
	EventQueue * EventQueue::queue;

	EventQueue::EventQueue() {
		size = 0;
	}

	EventQueue * EventQueue::getEventQueue() {
		if (!created) {
			queue = new EventQueue();
			created = true;
		}
		return queue;
	}

	Event * EventQueue::getNext() {
		Event * e = new Event();
		if (size >= 1) {
			e = events.front();
			events.pop_front();
			size -= 1;
		}
		return e;
	}

	void EventQueue::add(Event * e) {
		events.push_back(e);
		size += 1;
	}

	bool EventQueue::hasNext() {
		return size >= 1;
	}
}
