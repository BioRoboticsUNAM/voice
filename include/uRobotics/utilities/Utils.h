#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <sstream>
#include <boost/cstdint.hpp> 

namespace Robotics{ namespace Utilities{

class Utils{
public:
	static void trim(std::string& s);
	static unsigned int hashString(const std::string& s);
	static unsigned int hashString(const char* s);
	static bool convert(const std::string& input, boost::int8_t& value);
	static bool convert(const std::string& input, boost::int16_t& value);
	static bool convert(const std::string& input, boost::int32_t& value);
	static bool convert(const std::string& input, boost::int64_t& value);
	static bool convert(const std::string& input, float& value);
	static bool convert(const std::string& input, double& value);
	static void replace(std::string& str, const std::string& oldString, const std::string& newString);
};

template<typename T>
struct isPointer { static const bool value = false; };

template<typename T>
struct isPointer<T*> { static const bool value = true; };

} /* Utilities */ } /* Robotics */

#endif // __UTILS_H__