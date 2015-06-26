#ifndef __DOUBLE_SHARED_VARIABLE_H__
#define __DOUBLE_SHARED_VARIABLE_H__

#include <string>
#include <boost/cstdint.hpp> 
#include <uRobotics/api/SharedVariableGeneric.h>

class DoubleSharedVariable : public SharedVariableGeneric<double>{
private:
	DoubleSharedVariable(void);
	DoubleSharedVariable(const DoubleSharedVariable&);
public:
	DoubleSharedVariable(const std::string& name);
	DoubleSharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const double& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, double& value) const;
};

#endif // __DOUBLE_SHARED_VARIABLE_H__