#include "Misc.h"
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>

Misc::Misc(){}

Misc::Misc(const Misc&){}

Misc::~Misc(){}

void Misc::trim(std::string& s){
	size_t p = s.find_first_not_of(" \t\r\n");
		s.erase(0, p);
	p = s.find_last_not_of(" \t\r\n");
	if (std::string::npos != p)
		s.erase(p+1);
}


unsigned int Misc::hashString(const std::string& s){
	unsigned int a = 54059; // A prime
	unsigned int b = 76963; // Another prime
	unsigned int h = 31; // also prime
	for(size_t i = 0; i < s.size(); ++i) {
		h = (h * a) ^ (s[i] * b);
	}
	return h;
}

unsigned int Misc::hashString(const char* s){
	unsigned int a = 54059; // A prime
	unsigned int b = 76963; // Another prime
	unsigned int h = 31; // also prime
	while (*s) {
		h = (h * a) ^ (*s * b);
		s++;
	}
	return h;
}

bool Misc::convert(const std::string& input, bool& value){
	std::string tsd = boost::trim_copy(input);

	if((value = boost::iequals("true", input)) || boost::iequals("false", input))
		return true;

	int iValue;
	if (convert(tsd, iValue))
	{
		value = iValue != 0;
		return true;
	}
	return false;
}

bool Misc::convert(const std::string& input, boost::int8_t& value){
	boost::int32_t iValue;
	try{
		std::stringstream(input) >> iValue;
		value = (boost::int8_t)iValue;
		return true;
	}catch(...){ return false; }
}

bool Misc::convert(const std::string& input, boost::int16_t& value){
	std::stringstream ss(input);
	try{
		ss >> value;
		return true;
	}catch(...){ return false; }
}

bool Misc::convert(const std::string& input, boost::int32_t& value){
	try{
		std::stringstream(input) >> value;
		return true;
	}catch(...){ return false; }
}

bool Misc::convert(const std::string& input, boost::int64_t& value){
	try{
		std::stringstream(input) >> value;
		return true;
	}catch(...){ return false; }
}

bool Misc::convert(const std::string& input, float& value){
	try{
		std::stringstream(input) >> value;
		return true;
	}catch(...){ return false; }
}

bool Misc::convert(const std::string& input, double& value){
	try{
		std::stringstream(input) >> value;
		return true;
	}catch(...){ return false; }
}

void Misc::replace(std::string& str, const std::string& oldString, const std::string& newString){
	if(str.empty() || oldString.empty())
		return;
	size_t start = 0;
	while((start = str.find(oldString, start)) != std::string::npos) {
		str.replace(start, oldString.length(), newString);
		start += newString.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

std::vector<char> Misc::decodeBase64(const std::string& encodedData){
	const std::string base64_padding[] = {"", "==","="};
	namespace bai = boost::archive::iterators;
	std::stringstream os;

	const char* begin = reinterpret_cast<const char*>(&encodedData[0]);
	typedef bai::transform_width<bai::binary_from_base64<const char *>, 8, 6> base64_dec;
	size_t size = encodedData.size();
	size_t decodedSize = 3 * size / 4;

	// Remove the padding characters, cf. https://svn.boost.org/trac/boost/ticket/5629
	if (size && encodedData[size - 1] == '=') {
		--size;
		--decodedSize;
		if (size && encodedData[size - 1] == '='){
			--size;
			--decodedSize;
		}
	}

	if (size == 0) return std::vector<char>();
	std::vector<char> decoded = std::vector<char>(decodedSize);

	std::copy(base64_dec(encodedData.data()), base64_dec(encodedData.data() + size), &decoded[0]);

	return decoded;
}

std::string Misc::encodeBase64(const std::vector<char>& data){
	const std::string base64_padding[] = {"", "==","="};
	namespace bai = boost::archive::iterators;
	std::stringstream os;

	const char* begin = reinterpret_cast<const char*>(&data[0]);
	const char* end = (const char*)(begin + data.size());

	// convert binary values to base64 characters
	typedef bai::base64_from_binary
		// retrieve 6 bit integers from a sequence of 8 bit bytes
		<bai::transform_width<const char *, 6, 8> > base64_enc; // compose all the above operations in to a new iterator

	std::copy(base64_enc(begin), base64_enc(end), std::ostream_iterator<char>(os));

	os << base64_padding[data.size() % 3];
	return os.str();
}

std::string Misc::getHomePath(){
	return boost::filesystem::canonical(boost::filesystem::path(std::getenv("HOME"))).string();
}

std::string Misc::getCanonicalPath(const std::string& path){
	if(path.empty())
		return boost::filesystem::current_path().string();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	return boost::filesystem::canonical(boost::filesystem::path(path)).string();
#else
	std::string p(path);
	if(p[0] == '~') p = getHomePath() + p.substr(1);
	boost::filesystem::path relative(p);
	boost::filesystem::path canonical(relative);
	return canonical.string();
#endif
}

void Misc::linuxRun(const std::string& command){
	#if !defined(WIN32) && !defined(_WIN32) && !defined(__WIN32) || defined(__CYGWIN__)
	system(command.c_str());
	#endif
}