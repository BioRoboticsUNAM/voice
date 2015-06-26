#ifndef __STOP_WATCH_H__
#define __STOP_WATCH_H__

namespace Robotics{ namespace Utilities{

class Stopwatch
{
private:
	long long startTime;
	long long currentTime;
	bool running;
	Stopwatch(const Stopwatch& other);

public:
	Stopwatch(void);
	virtual ~Stopwatch(void);
	void start();
	void stop();
	void reset();
	long elapsedMilliseconds();
	long long elapsedMicroseconds();
};

} /* Utilities */ } /* Robotics */

#endif // __STOP_WATCH_H__