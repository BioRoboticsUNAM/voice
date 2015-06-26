#ifndef __STRING_SHARED_VARIABLE_H__
#define __STRING_SHARED_VARIABLE_H__

#include <string>
#include <sstream>
#include <uRobotics/api/SharedVariableGeneric.h>

class StringSharedVariable : public SharedVariableGeneric<std::string>{
private:
	StringSharedVariable(void);
	StringSharedVariable(const StringSharedVariable&);
public:
	StringSharedVariable(const std::string& name);
	StringSharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const std::string& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, std::string& value) const;
};

#endif // __STRING_SHARED_VARIABLE_H__