/* 
 * File:   Exception.h
 * Author: Mauricio Matamoros
 *
 */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>
#include <exception>

namespace Robotics{

class Exception :
	public std::exception
{
private:
	std::string msg;
public:
	Exception(void) throw();
	Exception(const std::string& message);
	Exception(const char *message);
	virtual ~Exception(void) throw();
	virtual const char* what() const throw();
};

class ArgumentNullException
	: public Exception{
public:
	ArgumentNullException(void);
	ArgumentNullException(const std::string& parameterName);
};

class ArgumentOutOfRangeException
	: public Exception{
public:
	ArgumentOutOfRangeException(void);
	ArgumentOutOfRangeException(const std::string& parameterName);
};

}

#endif // __EXCEPTION_H__
