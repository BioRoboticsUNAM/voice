/* 
 * File:   SharedVariableReportType.h
 * Author: Mauricio Matamoros
 *
 */

#include <string>
#include <uRobotics/Enum.h>

#ifndef __SHARED_VARIABLE_REPORT_TYPE_H__
#define __SHARED_VARIABLE_REPORT_TYPE_H__

using namespace Robotics;

/**
* Specifies how a subscription report of a shared variable change is made
*/
class SharedVariableReportType : public Enum{
public:
	/**
	* The subscription status to the shared variable is unknown
	*/
	static const int Unknown = -1;
	/**
	* There is no subscription to the shared variable
	*/
	static const int None = 0;
	/**
	* Sends a report that just notifies the change of the content of a shared variable
	*/
	static const int Notify = 1;
	/**
	* Sends a report that notifies the change of the content of a shared variable sending it's content
	*/
	static const int SendContent = 2;
private:
	int value;
	SharedVariableReportType();
public:
	SharedVariableReportType(int v);
	SharedVariableReportType(const SharedVariableReportType&);
	virtual ~SharedVariableReportType();
	static const bool tryParse(const std::string& s, SharedVariableReportType& type);
	//operator SharedVariableReportType() const { return this->value; }
};

#endif // __SHARED_VARIABLE_REPORT_TYPE_H__