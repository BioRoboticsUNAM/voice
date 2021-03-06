/* 
 * File:   Misc.hpp
 * Author: Mauricio Matamoros
 *
 */

#ifndef __MISC_H__
#define __MISC_H__

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/cstdint.hpp> 

namespace voice{
	class Misc{
	private:
		Misc();
		Misc(const Misc&);
		virtual ~Misc();
	public:
		static void trim(std::string& s);
		static unsigned int hashString(const std::string& s);
		static unsigned int hashString(const char* s);
		static bool convert(const std::string& input, bool& value);
		static bool convert(const std::string& input, boost::int8_t& value);
		static bool convert(const std::string& input, boost::int16_t& value);
		static bool convert(const std::string& input, boost::int32_t& value);
		static bool convert(const std::string& input, boost::int64_t& value);
		static bool convert(const std::string& input, float& value);
		static bool convert(const std::string& input, double& value);
		static std::vector<char> decodeBase64(const std::string& encodedData);
		static std::string encodeBase64(const std::vector<char>& data);
		static void replace(std::string& str, const std::string& oldString, const std::string& newString);
		
		static std::string getHomePath();
		static std::string getCanonicalPath(const std::string& path);
		static void linuxRun(const std::string& command);
	};

	template<typename T>
	struct isPointer { static const bool value = false; };

	template<typename T>
	struct isPointer<T*> { static const bool value = true; };

}

#endif // __MISC_H__