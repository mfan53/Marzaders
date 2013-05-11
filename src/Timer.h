#ifndef INC_ARSENAL_TIMER_H
#define INC_ARSENAL_TIMER_H

namespace Arsenal {
	class Timer {
	public:
		Timer(float time = 0, float elapsed = 0);
		virtual ~Timer();

		// Returns true if this timer has elapsed the amount of time it records
		bool check() { if(m_time < m_elapsed) { m_elapsed = 0; return true; } return false; };
		// Updates the timer then checks it
		bool check(float delta) { m_elapsed += delta; return check(); };

	private:
		// The amount of time that this timer times for
		float m_time;
		// The amount of time that this timer has recorded
		float m_elapsed;
	};
}

#endif // INC_ARSENAL_TIMER_H
