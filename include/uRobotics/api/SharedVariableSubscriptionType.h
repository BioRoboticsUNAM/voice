/* 
 * File:   SharedVariableSubscriptionType.h
 * Author: Mauricio Matamoros
 *
 */
#ifndef __SHARED_VARIABLE_SUBSCRIPTION_TYPE_H__
#define __SHARED_VARIABLE_SUBSCRIPTION_TYPE_H__

#include <string>
#include <uRobotics/Enum.h>

using namespace Robotics;

/**
* Specifies the type of subscription to a SharedVariable object
*/
class SharedVariableSubscriptionType : public Enum
 {
 public:
	/**
	* The subscription status to the shared variable is unknown
	*/
	static const int Unknown = -1;
	/**
	* There is no subscription to the shared variable
	*/
	static const int None  = 0;
	/**
	* Subscribes to the creation of a variable by any module
	*/
	static const int Creation = 1;
	/**
	* Subscribes to the creation of a variable by any module
	*/
	static const int WriteAny = 2;
	/**
	* Subscribes to the writing of a variable by any module different from the subscriber one
	*/
	static const int WriteOthers = 3;
	/**
	* Subscribes to the writing of a variable by th specified module
	*/
	static const int WriteModule = 4;
private:
	SharedVariableSubscriptionType();
public:
	SharedVariableSubscriptionType(int v);
	SharedVariableSubscriptionType(const SharedVariableSubscriptionType&);
	virtual ~SharedVariableSubscriptionType();
	static const bool tryParse(const std::string& s, SharedVariableSubscriptionType& type);
};

#endif // __SHARED_VARIABLE_SUBSCRIPTION_TYPE_H__