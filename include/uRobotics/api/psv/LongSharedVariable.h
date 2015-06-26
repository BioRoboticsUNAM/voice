#ifndef __LONG_SHARED_VARIABLE_H__
#define __LONG_SHARED_VARIABLE_H__

#include <string>
#include <boost/cstdint.hpp> 
#include <uRobotics/api/SharedVariableGeneric.h>

class LongSharedVariable : public SharedVariableGeneric<boost::int64_t>{
private:
	LongSharedVariable(void);
	LongSharedVariable(const LongSharedVariable&);
public:
	LongSharedVariable(const std::string& name);
	LongSharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const boost::int64_t& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, boost::int64_t& value) const;
};

#endif // __LONG_SHARED_VARIABLE_H__