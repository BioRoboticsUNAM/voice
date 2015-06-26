/* 
 * File:   uRobotics.h
 * Author: Mauricio Matamoros
 *
 */

#pragma once
#ifndef __SHARED_VARIABLE_REPORT_H__
#define __SHARED_VARIABLE_REPORT_H__

#include <string>
#include "uRobotics/Exception.h"
#include "uRobotics/api/Response.h"
#include "uRobotics/api/ISharedVariableInfo.h"
#include "uRobotics/api/SharedVariableInfo.h"
#include "uRobotics/api/SharedVariableReportType.h"
#include "uRobotics/api/SharedVariableSubscriptionType.h"

class SharedVariableReport
{
	private:
		/**
		* The type of the report
		*/
		SharedVariableReportType reportType;

		/**
		* The serialized data received with the report
		*/
		std::string serializedData;

		/**
		* The type of the subscription
		*/
		SharedVariableSubscriptionType subscriptionType;

		/**
		* The name of the module which performed the write/create operation
		*/
		std::string writer;

		/**
		* Stores the information of the related shared variable
		*/
		const ISharedVariableInfo* variableInfo;

	private: SharedVariableReport(void);
	public:
		/**
		* Initializes a new instance of SharedVariableReport
		* @param variableInfo The information of the related shared variable
		* @param serializedData The serialized value of the shared variable
		* @param reportType The type of the report
		* @param subscriptionType The type of the subscription
		* @param writer  The name of the module which performed the write/create operation
		*/
		SharedVariableReport(const ISharedVariableInfo* variableInfo, const std::string& serializedData,
			const SharedVariableReportType& reportType, const SharedVariableSubscriptionType& subscriptionType, const std::string& writer);

		virtual ~SharedVariableReport(void);

		/**
		* Gets the type of the report
		*/
		const SharedVariableReportType getReportType() const;

		/**
		* Gets the serialized data received with the report
		*/
		const std::string getSerializedData() const;

		/**
		* Gets the type of the subscription
		*/
		const SharedVariableSubscriptionType getSubscriptionType() const;

		/**
		* Gets the information of the related shared variable
		*/
		const ISharedVariableInfo* getVariableInfo() const;

		/**
		* Gets the name of the module which performed the write/create operation
		*/
		const std::string getWriter() const;

	private:

		static bool getVariableInfo(std::string& parameters, SharedVariableInfo*& info, std::string& data, Exception& ex);

		static bool getWriter(std::string& parameters, std::string& writer, Exception& ex);

		static bool getSubscriptionType(std::string& parameters, SharedVariableSubscriptionType& subscriptionType, Exception& ex);

		static bool getReportType(std::string& parameters, SharedVariableReportType& reportType, Exception& ex);

		static bool getVariableType(std::string& parameters, size_t& cc, std::string& type, bool& isArray, int& size, Exception& ex);

		static bool getVariableName(std::string& parameters, size_t& cc, std::string& name, Exception& ex);

		static bool getVariableData(std::string& parameters, size_t& cc, std::string& data, Exception& ex);

	public:

		/**
		* Generates a SharedVariableReport object from a Response object
		* @param response The Response object to be used to generate the report
		* @return A SharedVariableReport object created from the Response object
		*/
		static SharedVariableReport* createFromResponse(const Response& response);
		/**
		* Generates a SharedVariableReport object from a Response object
		* @param response The Response object to be used to generate the report
		* @param report When this method returns contains the SharedVariableReport object
		* extracted from the response if the parse operation was completed successfully, null otherwise
		* @param ex When this method returns contains null if the parse operation was completed successfully,
		* or the exception to be thrown if the operation failed
		* @return A SharedVariableReport object created from the Response object
		*/
		//internal
		static bool createFromResponse(const Response& response, SharedVariableReport*& report, Exception& ex);
		/**
		* Generates a SharedVariableReport object from a Response object
		* @param response The Response object to be used to generate the report
		* @param report When this method returns contains the SharedVariableReport object
		* extracted from the response if the parse operation was completed successfully, null otherwise
		* @return A SharedVariableReport object created from the Response object
		*/
		//internal
		static bool createFromResponse(const Response& response, SharedVariableReport*& report);
};

#endif // __SHARED_VARIABLE_REPORT_H__

