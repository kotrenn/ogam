#ifndef __TIMER_H
#define __TIMER_H

#include "common.h"

class Timer
{
public:
	Timer();
	Timer(double time);

	void pause();
	void unpause();
	void reset(double time);
	void clear();

	double get_time() const;
	double cycles_elapsed(double cycle) const;
	bool done() const { return get_time() <= 0; }
private:
	Uint32 m_start;
	Uint32 m_pause;
	double m_time;
	bool m_paused;
};

#endif
