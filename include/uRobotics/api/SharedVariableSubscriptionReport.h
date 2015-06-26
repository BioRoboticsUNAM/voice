/* 
 * File:   SharedVariableSubscriptionReport.h
 * Author: Mauricio Matamoros
 *
 */

#include <string>
#include "SharedVariable.h"
#include "SharedVariableReportType.h"
#include "SharedVariableSubscriptionType.h"

#ifndef __SHARED_VARIABLE_SUBSCRIPTION_REPORT_H__
#define __SHARED_VARIABLE_SUBSCRIPTION_REPORT_H__

template <class T>
class SharedVariableSubscriptionReport
{
protected:
	/**
	* The SharedVariable object that generates this report
	*/
	SharedVariable* variable;

	/**
	* The type of report received
	*/
	SharedVariableReportType reportType;

	/**
	* The type of subscription of the report received
	*/
	SharedVariableSubscriptionType subscriptionType;

	/**
	* The name of the module that performed the write or create operation
	*/
	std::string writer;

	/**
	* The value of the data contained in the report
	*/
	T value;

public:

	virtual ~SharedVariableSubscriptionReport(void);
	/**
	* Initializes a new instance of SharedVariableSubscriptionReport
	* @param variable The SharedVariable object that generates this report
	* @param subscriptionType The type of subscription of the report received
	* @param reportType The type of report received
	* @param writer The name of the module that performed the write or create operation
	* @param value The value of the data contained in the report
	*/
	SharedVariableSubscriptionReport(SharedVariable* variable, SharedVariableReportType reportType, SharedVariableSubscriptionType subscriptionType, std::string writer, T value);

	/**
	*Gets the SharedVariable object that generates this report
	*/
	SharedVariable* getVariable() const;

	/**
	*Gets the type of report received
	*/
	SharedVariableReportType& getReportType() const;

	/**
	*Gets the type of subscription of the report received
	*/
	SharedVariableSubscriptionType& getSubscriptionType() const;

	/**
	*Gets the name of the module that performed the write or create operation
	*/
	std::string& getWriterName() const;

	/**
	*Gets the value of the data contained in the report
	*/
	const T& getValue() const;

	std::string toString() const;
};

template <class T>
SharedVariableSubscriptionReport<T>::SharedVariableSubscriptionReport(SharedVariable* variable, SharedVariableReportType reportType, SharedVariableSubscriptionType subscriptionType, std::string writer, T value):
variable(variable), reportType(reportType), subscriptionType(subscriptionType), writer(writer), value(value){}

template <class T>
SharedVariableSubscriptionReport<T>::~SharedVariableSubscriptionReport(void){}

template <class T>
SharedVariable* SharedVariableSubscriptionReport<T>::getVariable() const{
	return variable;
}

template <class T>
SharedVariableReportType& SharedVariableSubscriptionReport<T>::getReportType() const{
	return reportType;
}

template <class T>
SharedVariableSubscriptionType& SharedVariableSubscriptionReport<T>::getSubscriptionType() const{
	return subscriptionType;
}

template <class T>
std::string& SharedVariableSubscriptionReport<T>::getWriterName() const{
	return writer;
}

template <class T>
const T& SharedVariableSubscriptionReport<T>::getValue() const{
	return value;
}

template <class T>
std::string SharedVariableSubscriptionReport<T>::toString() const{
	std::stringstream ss;
	ss << "ShVReport<T>{ "<< variable->getTypeName();
		if (variable->isArray()){
			ss << "[";
			if (variable->getLength() > -1) ss << variable->getLength();
			ss << "]";
		}
		ss << " " << variable->getName() << " " << value << " } " <<
			subscriptionType << " % " <<
			reportType << " % " <<
			writer;
		return ss.str();
	}


#endif // __SHARED_VARIABLE_SUBSCRIPTION_REPORT_H__

