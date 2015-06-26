#ifndef __LASER_READING_ASV_H__
#define __LASER_READING_ASV_H__

#include <uRobotics/hal/sensors/telemetric/LaserReading.h>
#include <uRobotics/api/SharedVariableGeneric.h>

using namespace Robotics::HAL::Sensors::Telemetric;

/*

class LaserReadingASV : public SharedVariableGeneric< std::vector<LaserReading> >
{
private:
	LaserReadingASV(void);
	LaserReadingASV(const LaserReadingASV&);
public:
	LaserReadingASV(const std::string& name);
	LaserReadingASV(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const std::vector<LaserReading>& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, std::vector<LaserReading>& value) const;
};

*/
#endif // __LASER_READING_ASV_H__
