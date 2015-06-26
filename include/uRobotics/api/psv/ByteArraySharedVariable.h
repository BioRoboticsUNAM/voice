#ifndef __BYTE_ARRAY_SHARED_VARIABLE_H__
#define __BYTE_ARRAY_SHARED_VARIABLE_H__

#include <string>
#include <boost/cstdint.hpp> 
#include <uRobotics/api/SharedVariableGeneric.h>

class ByteArraySharedVariable : public SharedVariableGeneric< std::vector<boost::int8_t> >{
private:
	ByteArraySharedVariable(void);
	ByteArraySharedVariable(const ByteArraySharedVariable&);
public:
	ByteArraySharedVariable(const std::string& name);
	ByteArraySharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const std::vector<boost::int8_t>& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, std::vector<boost::int8_t>& value) const;
};

#endif // __BYTE_ARRAY_SHARED_VARIABLE_H__
