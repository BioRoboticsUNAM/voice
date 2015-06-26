#ifndef __LONG_ARRAY_SHARED_VARIABLE_H__
#define __LONG_ARRAY_SHARED_VARIABLE_H__

#include <string>
#include <boost/cstdint.hpp> 
#include <uRobotics/api/SharedVariableGeneric.h>

class LongArraySharedVariable : public SharedVariableGeneric< std::vector<boost::int64_t> >{
private:
	LongArraySharedVariable(void);
	LongArraySharedVariable(const LongArraySharedVariable&);
public:
	LongArraySharedVariable(const std::string& name);
	LongArraySharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const std::vector<boost::int64_t>& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, std::vector<boost::int64_t>& value) const;
};



#endif // __LONG_ARRAY_SHARED_VARIABLE_H__
