/* 
 * File:   ISharedVariableInfo.h
 * Author: Mauricio Matamoros
 *
 */

#pragma once
#ifndef __SHARED_VARIABLE_INFO_H__
#define __SHARED_VARIABLE_INFO_H__

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <uRobotics/Exception.h>
#include <uRobotics/api/ISharedVariableInfo.h>
#include <uRobotics/api/SubscriptionInfo.h>

class SharedVariableInfo :
	public ISharedVariableInfo
{
	private:
		/**
		* Indicates if the variable is an array
		*/
		bool isArray_;

		/**
		* The variable is an array gets the length of the array, else returns -1
		*/
		int length;

		/**
		* The name of the SharedVariable
		*/
		std::string name;

		/**
		* The global name of the type of the SharedVariable
		*/
		std::string typeName;

	public:
		SharedVariableInfo(void);
		SharedVariableInfo(const SharedVariableInfo& other);
		SharedVariableInfo(const std::string& typeName, const std::string& name);
		SharedVariableInfo(const std::string& typeName, const std::string& name, const bool& isArray, const int& length);
		virtual ~SharedVariableInfo(void);

		/**
		* Gets a value indicating if the variable is an array
		*/
		const virtual bool isArray() const;

		/**
		* If the variable is an array gets the length of the array, else returns -1
		*/
		const virtual int getLength() const;

		/**
		* Gets the name of the SharedVariable
		*/
		const virtual std::string getName() const;

		/**
		* Gets the global name of the type of the SharedVariable
		*/
		const virtual std::string getTypeName() const;

		/**
		* No info about the shared variable
		*/
		static const SharedVariableInfo None;

		static bool deserialize(const std::string& serialized, SharedVariableInfo& info);

		static bool deserialize(const std::string& serialized, SharedVariableInfo& info, Exception& ex);

	private:
		static bool deserializeSVInfo(const std::string& serialized, size_t& cc, SharedVariableInfo& info, Exception& ex);
		static bool deserializeCreationTime(const std::string& serialized, size_t& cc, boost::posix_time::ptime& creationTime, Exception& ex);
		static bool deserializeWriters(const std::string& serialized, size_t& cc, std::vector<std::string>& writers, Exception& ex);
		static bool deserializeSubscriptions(SharedVariableInfo svInfo, const std::string& serialized, size_t& cc, std::vector<SubscriptionInfo*>& subscriptions, Exception& ex);
		static bool deserializeSubscription(SharedVariableInfo svInfo, const std::string& serialized, size_t& cc, SubscriptionInfo*& subscription,  Exception& ex);
		static bool deserializeSubscriber(const std::string& serialized, size_t& cc, std::string& subscriber, Exception& ex);
		static bool deserializeSubscriptionType(const std::string& serialized, size_t& cc, SharedVariableSubscriptionType& sType, Exception& ex);
		static bool deserializeReportType(const std::string& serialized, size_t& cc, SharedVariableReportType& rType, Exception& ex);
		static bool deserializeSubscriptionWriter(const std::string& serialized, size_t& cc, std::string& subscriber, Exception& ex);
};


#endif // __SHARED_VARIABLE_INFO_H__