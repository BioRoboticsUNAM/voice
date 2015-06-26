#ifndef __BYTE_SHARED_VARIABLE_H__
#define __BYTE_SHARED_VARIABLE_H__

#include <string>
#include <boost/cstdint.hpp> 
#include <uRobotics/api/SharedVariableGeneric.h>

class ByteSharedVariable : public SharedVariableGeneric<boost::int8_t>{
private:
	ByteSharedVariable(void);
	ByteSharedVariable(const ByteSharedVariable&);
public:
	ByteSharedVariable(const std::string& name);
	ByteSharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const boost::int8_t& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, boost::int8_t& value) const;
};

#endif // __BYTE_SHARED_VARIABLE_H__