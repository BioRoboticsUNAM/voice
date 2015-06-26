#ifndef __DOUBLE_ARRAY_SHARED_VARIABLE_H__
#define __DOUBLE_ARRAY_SHARED_VARIABLE_H__

#include <string>
#include <boost/cstdint.hpp> 
#include <uRobotics/api/SharedVariableGeneric.h>

class DoubleArraySharedVariable : public SharedVariableGeneric< std::vector<double> >{
private:
	DoubleArraySharedVariable(void);
	DoubleArraySharedVariable(const DoubleArraySharedVariable&);
public:
	DoubleArraySharedVariable(const std::string& name);
	DoubleArraySharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const std::vector<double>& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, std::vector<double>& value) const;
};

#endif // __DOUBLE_ARRAY_SHARED_VARIABLE_H__
