#ifndef __LASER_READING_H__
#define __LASER_READING_H__

#include <uRobotics/hal/sensors/telemetric/ITelemetricReading.h>

namespace Robotics{ namespace HAL{ namespace Sensors{ namespace Telemetric{

class LaserReading : public ITelemetricReading
{
public:
	LaserReading(void);
	~LaserReading(void);
};

} /*Telemetric*/} /*Sensors*/ } /*HAL*/ } /*Robotics*/

#endif // __LASER_READING_H__