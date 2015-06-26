#ifndef __VAR_SHARED_VARIABLE_H__
#define __VAR_SHARED_VARIABLE_H__

#include <string>
#include <sstream>
#include <uRobotics/api/SharedVariableGeneric.h>

class VarSharedVariable : public SharedVariableGeneric<std::string>{
private:
	VarSharedVariable(void);
	VarSharedVariable(const VarSharedVariable&);
public:
	VarSharedVariable(const std::string& name);
	VarSharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const std::string& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, std::string& value) const;
};

#endif // __VAR_SHARED_VARIABLE_H__