#pragma once
#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <algorithm> // std::min / std::max

namespace Robotics{ namespace Utilities{

class Scanner{
/************************************************************************/
/* Methods                                                              */
/************************************************************************/
public:
	static bool advanceToChar(const char& c, const std::string& input, size_t& cc);

	static bool advanceToChar(const std::vector<char>& c, const std::string& input, size_t& cc);

	static bool readChar(const char& c, const std::string& input, size_t& cc);

	static bool readString(const std::string& expected, const std::string& input, size_t& cc);

	static void skipSpaces(const std::string& s, size_t& cc);

	static bool xtractByte(const std::string& input, size_t& cc, unsigned char& value);

	static bool xtractSByte(const std::string& input, size_t& cc, signed char& value);

	static bool xtractUInt16(const std::string& input, size_t& cc, unsigned short& value);

	static bool xtractInt16(const std::string& input, size_t& cc, short& value);

	static bool xtractUInt32(const std::string& input, size_t& cc, unsigned int& value);

	static bool xtractInt32(const std::string& input, size_t& cc, int& value);
	
	static bool xtractSingle(const std::string& input, size_t& cc, float& value);

	static bool xtractDouble(const std::string& input, size_t& cc, double& value);

	static bool isAlNum(char c);

	static bool isAlpha(char c);

	static bool isLAlpha(char c);

	static bool isLAlNum(char c);

	static bool isNumeric(char c);

	static bool isSpace(char c);

	static bool isUAlpha(char c);

	static bool isUAlNum(char c);
};

} /* Utilities */ } /* Robotics */

#endif // __SCANNER_H__
