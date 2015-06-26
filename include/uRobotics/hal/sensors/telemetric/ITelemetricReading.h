#ifndef __I_TELEMETRIC_READING_H__
#define __I_TELEMETRIC_READING_H__

namespace Robotics{ namespace HAL{ namespace Sensors{ namespace Telemetric{

class ITelemetricReading{

	/**
	* Indicates if an obstacle was detected by this reading
	*/
	virtual bool obstacleDetected() const = 0;

	/**
	* Gets the x-coordinate of the Cartesian transform of this reading in meters.
	*/
	virtual double getX() const = 0;

	/**
	* Gets the y-coordinate of the Cartesian transform of this reading in meters
	*/
	virtual double getY() const = 0;
};

} /*Telemetric*/} /*Sensors*/ } /*HAL*/ } /*Robotics*/

#endif // __I_TELEMETRIC_READING_H__