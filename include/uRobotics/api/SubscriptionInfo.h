#ifndef __SUBSCRIPTION_INFO_H__ 
#define __SUBSCRIPTION_INFO_H__

#include <string>
#include <uRobotics/api/ISharedVariableInfo.h>
#include <uRobotics/api/SharedVariableReportType.h>
#include <uRobotics/api/SharedVariableSubscriptionType.h>

class SubscriptionInfo
{
private:
	/**
	* The name of the subscriber module
	*/
	std::string moduleName;

	/**
	* The subscription type of the subscriber module
	*/
	SharedVariableSubscriptionType subscriptionType;

	/**
	* The report type for the subscription of the subscriber module
	*/
	SharedVariableReportType reportType;

	/**
	* The object which contains information about the shared variable related to the subscription
	*/
	ISharedVariableInfo& variableInfo;

	/**
	* The name of the writer module for subscription types which allows to set an specific module
	*/
	std::string writerModule;

public:
	~SubscriptionInfo(void);
	SubscriptionInfo(ISharedVariableInfo& variableInfo);
	SubscriptionInfo(ISharedVariableInfo& variableInfo, const std::string& moduleName,
		const SharedVariableSubscriptionType& subscriptionType, const SharedVariableReportType& reportType);
	SubscriptionInfo(ISharedVariableInfo& variableInfo, const std::string& moduleName,
		const SharedVariableSubscriptionType& subscriptionType, const SharedVariableReportType& reportType, const std::string& writerModule);

	/**
	* Gets or sets the name of the subscriber module
	*/
	std::string getModuleName() const;
	void setModuleName(const std::string& value);

	/**
	* Gets or sets the subscription type of the subscriber module
	*/
	SharedVariableSubscriptionType getSubscriptionType() const;
	void setSubscriptionType(const SharedVariableSubscriptionType& value);

	/**
	* Gets or sets the report type for the subscription of the subscriber module
	*/
	SharedVariableReportType getReportType() const;
	void setReportType(const SharedVariableReportType& value);

	/**
	* Gets or sets information about the shared variable related to the subscription
	*/
	ISharedVariableInfo& getVariableInfo();
	void setVariableInfo(ISharedVariableInfo& value);

	/**
	* Gets or sets the name of the writer module for subscription types which allows to set an specific module
	*/
	std::string getWriterModule() const;
	void setWriterModule(const std::string& value);

};

#endif // __SUBSCRIPTION_INFO_H__


