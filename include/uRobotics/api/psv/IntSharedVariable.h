#ifndef __INT_SHARED_VARIABLE_H__
#define __INT_SHARED_VARIABLE_H__

#include <string>
#include <boost/cstdint.hpp> 
#include <uRobotics/api/SharedVariableGeneric.h>

class IntSharedVariable : public SharedVariableGeneric<boost::int32_t>{
private:
	IntSharedVariable(void);
	IntSharedVariable(const IntSharedVariable&);
public:
	IntSharedVariable(const std::string& name);
	IntSharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const boost::int32_t& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, boost::int32_t& value) const;
};

#endif // __INT_SHARED_VARIABLE_H__