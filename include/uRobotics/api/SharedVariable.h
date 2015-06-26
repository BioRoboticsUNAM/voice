/* 
 * File:   SharedVariable.h
 * Author: Mauricio Matamoros
 *
 */

#pragma once
#ifndef __SHARED_VARIABLE_H__
#define __SHARED_VARIABLE_H__

#include <string>
#include <boost/signals2.hpp>
#include "uRobotics/api/Command.h"
#include "uRobotics/api/Response.h"
#include "uRobotics/api/SharedVariableInfo.h"
#include "uRobotics/api/ISharedVariableInfo.h"
#include "uRobotics/api/SharedVariableReport.h"
#include "uRobotics/api/SharedVariableReportType.h"
#include "uRobotics/api/SharedVariableSubscriptionType.h"
#include <uRobotics/Exception.h>

class SharedVariableReport;
class SharedVariableList;
class SimpleCommandManager;

class SharedVariable :
	public ISharedVariableInfo
{
	friend class SharedVariableList;
	friend class SimpleCommandManager;
	protected:
		/**
		* The CommandManager object used to communicate with the Blackboard
		*/
		SimpleCommandManager* commandManager;
	public:
		SharedVariable(void);
		virtual ~SharedVariable(void);

		/**
		Gets a value indicating if the variable has been initialized (created or read from blackboard)
		*/
		const virtual bool getInitialized() const = 0;

		/**
		Gets a value indicating if the variable is an array
		*/
		const virtual bool isArray() const = 0;

		/**
		If the variable is an array gets the length of the array, else returns -1
		*/
		const virtual int getLength() const = 0;

		/**
		Gets the name of the SharedVariable
		*/
		const virtual std::string getName() const = 0;

		/**
		Gets the global name of the type of the SharedVariable
		*/
		const virtual std::string getTypeName() const = 0;

		/**
		* Connects to the remote variable. If the remote variable does not exist it is created.
		*/
		virtual void initialize() = 0;

		const SimpleCommandManager* getCommandManager() const;

		virtual void setCommandManager(SimpleCommandManager* value);

		/**
		* Request the blackboard to notify each time the shared variable is written
		*/
		virtual void subscribe();

		/**
		* Request the blackboard to notify each time the shared variable is written
		* @param reportType	The type of report. This affects the event that will be raised when the variable is written
		*/
		virtual void subscribe(const SharedVariableReportType& reportType);

		/**
		* Request the blackboard to notify each time the shared variable is written
		* @param subscriptionType	The type of subscription
		*/
		virtual void subscribe(const SharedVariableSubscriptionType& subscriptionType);

		/**
		* Request the blackboard to notify each time the shared variable is written
		* @param reportType	The type of report. This affects the event that will be raised when the variable is written
		* @param subscriptionType	The type of subscription
		*/
		virtual void subscribe(const SharedVariableReportType& reportType, const SharedVariableSubscriptionType& subscriptionType);

		/**
		* Request the blackboard to notify each time the shared variable is written
		* @param reportType	The type of report. This affects the event that will be raised when the variable is written
		* @param subscriptionType	The type of subscription
		* @param timeout	The time out for each subscription attempt in milliseconds
		* @param attempts	The number of subscription attempts to perform
		*/
		virtual void subscribe(SharedVariableReportType reportType, SharedVariableSubscriptionType subscriptionType, const int& timeout, const int& attempts) = 0;

		/**
		* Request the blackboard to stop notifying each time the shared variable is written
		*/
		void unsubscribe();

		/**
		* Request the blackboard to stop notifying each time the shared variable is written
		* @param timeout	The timeout for each unsubscription attempt (of 3) in milliseconds
		*/
		void unsubscribe(const int& timeout);

		/**
		* Request the blackboard to stop notifying each time the shared variable is written
		* @param timeout	The time out for each unsubscription attempt in milliseconds
		* @param attempts	The number of unsubscription attempts to perform
		*/
		virtual void unsubscribe(const int& timeout, const int& attempts) = 0;

		/**
		* Returns the string representation of the shared variable
		* @return The string representation of the shared variable
		*/
		const std::string toString() const;

		/**
		* Performs a read operation and updates the data stored in cache
		* @return true if the the data acquisition operation succeeded, false otherwise
		*/
		virtual bool updateBufferedData();

		/**
		* Performs a read operation and updates the data stored in cache
		* @param timeout	The amout of time to wait for a read confirmation from blackboard
		* @return true if the the data acquisition operation succeeded, false otherwise
		*/
		virtual bool updateBufferedData(const int& timeout) = 0;

		/**
		* Queries the Blackboard for updated information (writers and subscriptions) about the Shared Variable
		*/
		void updateInfo();

		/**
		* Decodes the data contained in a received response. A return value indicates whether the operation succeeded
		* @param response Response which contains the data to parse
		* @param variableType When this method returns contains the type of the variable coded in the response parameters if the conversion succeeded, or null if the conversion failed.
		* @param isArray When this method returns is set to true if the conversion succed and the variable coded in the response parameters is an array, false otherwise.
		* @param arrayLength When this method returns contains the size of the array if the conversion succed and the variable coded in the response parameters is an array, -1 otherwise.
		* @param variableName When this method returns contains the name of the variable coded in the response parameters if the conversion succeeded, or null if the conversion failed.
		* @param variableData When this method returns contains the content of the variable coded in the response parameters if the conversion succeeded, or the null if the conversion failed.
		* @return true if the the data extraction succeeded, false otherwise
		*/
		static bool parseResponse(const Response& response, std::string& variableType, bool& isArray, int& arrayLength, std::string& variableName, std::string& variableData);

		/**
		* Writes the provided value to the blackboard variable asociated to this SharedVariable object
		* @param value	The value to write in to the blackboard shared variable
		*/
		//virtual void Write<T>(T value) = 0;

		/** <summary>
		* Occurs when a report is received from the blackboard due to a subscription
		*/
		boost::signals2::signal<void(const SharedVariable&, const SharedVariableReport&)> reportReceived;

		/** <summary>
		* Occurs when the value of the shared variable is updated
		*/
		boost::signals2::signal<void(const SharedVariable&)> updated;

	// Internals
	protected:

		/**
		* Updates the SharedVariable object with data provided from the blackboard due to a subscription
		* @param svReport	The report which contains the information for update
		* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
		* @return true if variable was updated successfully, false otherwise
		*/
		virtual bool update(const SharedVariableReport& svReport, Exception& ex) = 0;

		/**
		* Updates the SharedVariable object with data provided from the blackboard due to a subscription
		* @param variableType	The type of the variable specified by blackboard
		* @param variableName	The name of the variable specified by blackboard
		* @param isArray	Value that indicates if the variable specified by blackboard is an array
		* @param arraySize	The size of the variable specified by blackboard if it is an array
		* @param sData	The serialized data contained in the report
		* @param reportType	The type of report
		* @param subscriptionType	The type of subscription
		* @param writer	The name of the module which performed the write/create operation
		* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
		* @return true if variable was updated successfully, false otherwise
		*/
		bool update(const std::string& variableType, const bool& isArray, const int& arraySize, const std::string& variableName,
			const std::string& sData, const SharedVariableReportType& reportType,
			const SharedVariableSubscriptionType& subscriptionType, const std::string& writer, Exception& ex);

		/**
		* Updates the SharedVariable object with data provided from the blackboard
		* @param variableType	The type of the variable specified by blackboard
		* @param variableName	The name of the variable specified by blackboard
		* @param isArray	Value that indicates if the variable specified by blackboard is an array
		* @param arraySize	The size of the variable specified by blackboard if it is an array
		* @param data	The serialized data stored in blackboard
		* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
		* @return true if variable was updated successfully, false otherwise
		*/
		bool update(const std::string& variableType, const bool& isArray, const int& arraySize, const std::string& variableName, const std::string& data, Exception& ex);
		
	protected:
		/**
		* Gets a value indicating if the data provided from the blackboard for an update is valid
		* @param variableType	The type of the variable specified by blackboard
		* @param variableName	The name of the variable specified by blackboard
		* @param isArray	Value that indicates if the variable specified by blackboard is an array
		* @param arraySize	The size of the variable specified by blackboard if it is an array
		* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
		* @return true if provided data is suitable for update the variable, false otherwise
		*/
		virtual bool isValidUpdateData(const std::string& variableType, const bool& isArray, const int& arraySize, const std::string& variableName, Exception& ex);

		/**
		* Deserializes and updates the value of the shared variable
		* @param serializedData	The serialized data containing the new value for the shared variable
		* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
		* @return true if variable was updated successfully, false otherwise
		*/
		bool updateValue(const std::string& serializedData, Exception& ex);

		/**
		* Deserializes and updates the value of the shared variable
		* @param serializedData	The serialized data containing the new value for the shared variable
		* @param writerModuleName	The name of the module which performs the write operation
		* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
		* @return true if variable was updated successfully, false otherwise
		*/
		virtual bool updateValue(const std::string& serializedData, const std::string& writerModuleName, Exception& ex) = 0;

		/**
		* Queries the Blackboard for updated information (writers and subscriptions) about the Shared Variable
		* @param timeout	The amount of time to wait for a stat confirmation from blackboard
		* @param ex	When this method returns contains null if the variable information was updated successfully, or the exception to be thrown if the update failed
		* @return true if the information was updated successfully, false otherwise
		*/
		// internal
		bool updateInfo(const int& timeout, Exception& ex);

		void onReportReceived(const SharedVariableReport&);

		void onUpdated();

};

#endif // __SHARED_VARIABLE_H__