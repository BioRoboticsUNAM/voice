#ifndef __INT_ARRAY_SHARED_VARIABLE_H__
#define __INT_ARRAY_SHARED_VARIABLE_H__

#include <string>
#include <boost/cstdint.hpp> 
#include <uRobotics/api/SharedVariableGeneric.h>

class IntArraySharedVariable : public SharedVariableGeneric< std::vector<boost::int32_t> >{
private:
	IntArraySharedVariable(void);
	IntArraySharedVariable(const IntArraySharedVariable&);
public:
	IntArraySharedVariable(const std::string& name);
	IntArraySharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const std::vector<boost::int32_t>& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, std::vector<boost::int32_t>& value) const;
};

#endif // __INT_ARRAY_SHARED_VARIABLE_H__
