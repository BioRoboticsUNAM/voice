/* 
 * File:   SharedVariableGeneric.h
 * Author: Mauricio Matamoros
 *
 */

#pragma once
#ifndef __SHARED_VARIABLE_GENERIC_H__
#define __SHARED_VARIABLE_GENERIC_H__

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/signals2.hpp>
#include "Command.h"
#include "Response.h"
#include "SimpleCommandManager.h"
#include "SharedVariable.h"
#include "SharedVariableInfo.h"
#include "ISharedVariableInfo.h"
#include "SharedVariableReport.h"
#include "SharedVariableSubscriptionReport.h"
#include <uRobotics/utilities/ProducerConsumer.h>
#include <uRobotics/utilities/Utils.h>
#include <uRobotics/Exception.h>

template <class T>
class SharedVariableGeneric : public SharedVariable{
private:
	/**
	* Indicates if the variable has been initialized
	*/
	bool initialized;

	/**
	* The local time when the value of the shared variable was last updated
	*/
	boost::posix_time::ptime lastUpdate;

	/**
	* The name of the module which performed the last write operation over the shared variable if known,
	* otherwise it returns null.
	* This property returns always null if there is not a subscription to the shared variable.
	*/
	std::string lastWriter;
	
	/**
	* The subscription type for the current subscription to the shared variable
	*/
	SharedVariableSubscriptionType subscriptionType;

	/**
	* The report type for the current subscription to the shared variable
	*/
	SharedVariableReportType subscriptionReportType;

protected:
	/**
	* Stores a copy of the last bufferedData
	*/
	T previousBufferedData;

	/**
	* Stores a copy of the last read, received or writen value of the shared variable
	*/
	T bufferedData;

	/**
	* The name of the variable in the Blackboard
	*/
	const std::string variableName;

	public: boost::signals2::signal<void(const SharedVariableSubscriptionReport<T>&)> writeNotification;

	private: SharedVariableGeneric(void);
	private: SharedVariableGeneric(const SharedVariableGeneric& other);

	/**
	* Initializes a new instance of SharedVariable
	* @param variableName	The name of the variable in the Blackboard
	* <remarks>If there is no variable with the provided name in the blackboard, a new variable with the asociated name is created</remarks>
	*/
	public: SharedVariableGeneric(std::string variableName);

	/**
	* Initializes a new instance of SharedVariable
	* @param commandManager	The CommandManager object used to communicate with the Blackboard
	* @param variableName	The name of the variable in the Blackboard
	* @param initialize	Indicates if the shared variable will be automatically initialized if the commandManager is different from null
	* <remarks>If there is no variable with the provided name in the blackboard, a new variable with the asociated name is created</remarks>
	*/
	public: SharedVariableGeneric(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);

	public:	void setCommandManager(SimpleCommandManager* value);
	
	/**
	* Gets a value indicating if the variable has been initialized (created or readed from blackboard)
	*/
	public: const virtual bool getInitialized() const;

	/**
	* Gets a value indicating if the variable is an array
	*/
	public: const virtual bool isArray() const;

	/**
	* If the variable is an array gets the length of the array, else returns -1
	*/
	public: const virtual int getLength() const;

   	/**
	* Gets the name of the SharedVariable
	*/
	public: const virtual std::string getName() const;

	/**
	* Gets the global name of the type of the SharedVariable
	*/
	public: const virtual std::string getTypeName() const;

	/**
	* Connects to the remote variable. If the remote variable does not exist it is created.
	*/
	public: virtual void initialize();
	private: void initialize(T value);

	/**
	* Request the blackboard to notify each time the shared variable is written
	* @param reportType	The type of report. This affects the event that will be raised when the variable is written
	* @param subscriptionType	The type of subscription
	* @param timeout	The time out for each subscription attempt in milliseconds
	* @param attempts	The number of subscription attempts to perform
	*/
	public: virtual void subscribe(SharedVariableReportType reportType, SharedVariableSubscriptionType subscriptionType, const int& timeout, const int& attempts);

	/**
	* Request the blackboard to stop notifying each time the shared variable is written
	* @param timeout	The time out for each unsubscription attempt in milliseconds
	* @param attempts	The number of unsubscription attempts to perform
	*/
	public: virtual void unsubscribe(const int& timeout, const int& attempts);

	/**
	* Performs a read operation and updates the data stored in cache
	* @param timeout	The amout of time to wait for a read confirmation from blackboard
	* @return true if the the data acquisition operation succeeded, false otherwise
	*/
	public: virtual bool updateBufferedData(const int& timeout);

	/**
	* Updates the SharedVariable object with data provided from the blackboard due to a subscription
	* @param svReport	The report which contains the information for update
	* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
	* @return true if variable was updated successfully, false otherwise
	*/
	private: virtual bool update(const SharedVariableReport& svReport, Exception& ex);

	/**
	* Deserializes and updates the value of the shared variable
	* @param serializedData The serialized data containing the new value for the shared variable
	* @param value When this method returns contains the new value for the shared variable if the variable was updated successfully, or the default value for T if the update failed
	* @param name ex When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
	* @returns true if variable was updated successfully, false otherwise
	*/
	protected: bool updateValue(const std::string& serializedData, T& value, Exception& ex);

	/**
	* Deserializes and updates the value of the shared variable
	* @param serializedData	The serialized data containing the new value for the shared variable
	* @param writerModuleName	The name of the module which performs the write operation
	* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
	* @return true if variable was updated successfully, false otherwise
	*/
	protected: virtual bool updateValue(const std::string& serializedData, const std::string& writerModuleName, Exception& ex);

   /**
	* Deserializes and updates the value of the shared variable
	* @param serializedData	The serialized data containing the new value for the shared variable
	* @param writerModuleName	The name of the module which performs the write operation
	* @param value When this method returns contains the new value for the shared variable if the variable was updated successfully, or the default value for T if the update failed
	* @param ex	When this method returns contains null if the variable was updated successfully, or the exception to be thrown if the update failed
	* @return true if variable was updated successfully, false otherwise
	*/
	protected: bool updateValue(const std::string& serializedData, const std::string& writerModuleName, T& value, Exception& ex);

	/**
	* Gets the name of the module which performed the last write operation over the shared variable if known,
	* otherwise it returns null.
	* This property returns always null if there is not a subscription to the shared variable.
	*/
	public: const std::string& getLastWriter() const;
	protected: void setLastWriter(const std::string& value);

	/**
	* Gets a buffered copy of the last read, received or written value of the shared variable
	*/
	public: const T& getBufferedData();
	protected: void setBufferedData(const T& value);

	/**
	* Gets the report type for the current subscription to the shared variable
	*/
	public: const SharedVariableReportType& getSubscriptionReportType();
	protected: void setSubscriptionReportType(const SharedVariableReportType& value);

   	/**
	* Gets the subscription type for the current subscription to the shared variable
	*/
	public: const SharedVariableSubscriptionType& getSubscriptionType();
	protected: void setSubscriptionType(const SharedVariableSubscriptionType& vaue);

	private: bool getUpdatedSerializedData(const int& timeout, std::string& serializedData, Exception& ex);

	/**
	* Gets the value stored in the blackboard for the SharedVariable represented by this object
	* @param timeout	The amount of time to wait for a read confirmation from blackboard
	* @return The value stored in the blackboard for the SharedVariable represented by this object
	*/
	public: T read(const int& timeout);
	/**
	* Gets the value stored in the blackboard for the SharedVariable represented by this object
	* @return The value stored in the blackboard for the SharedVariable represented by this object
	*/
	public: T read();
	/**
	* Gets the value stored in the blackboard for the SharedVariable represented by this object. A return value indicates whether the acquisition operation succeeded
	* @param value	When this method returns, contains the value stored in the blackboard for the SharedVariable represented by this object, if the conversion succeeded, or the default value of the type if the conversion failed.
	* @param timeout	The amount of time to wait for a read confirmation from blackboard
	* @param ex	When this method returns false contains the exception generated
	* @return true if the the data acquisition operation succeeded, false otherwise
	*/
	protected: bool read(T& value, const int& timeout, Exception& ex);

	/**
	* Writes the provided value to the blackboard variable associated to this SharedVariable object
	* @param value	The value to write in to the blackboard shared variable
	*/
	public: void write(const T& value);

	/**
	* Writes the provided value to the blackboard variable associated to this SharedVariable object
	* @param value	The value to write in to the blackboard shared variable
	* @param timeout	The amount of time to wait for a write confirmation from blackboard. Use Zero to write without wait for confirmation. Use -1 to wait indefinitely
	*/
	public: void write(const T& value, const int& timeout);
	/**
	* Writes the provided value to the blackboard variable associated to this SharedVariable object. A return value indicates whether the write operation succeeded
	* @param value	The value to write in to the blackboard shared variable
	* @param timeout	The amount of time to wait for a write confirmation from blackboard
	* @param ex	When this method returns false contains the exception generated
	* @return true if the the data write operation succeeded, false otherwise
	*/
	protected: bool write(const T& value, const int& timeout, Exception& ex);

	/**
	* Extracts the variable data from a response
	* @param response	Response which contains the data to extract
	* @param variableData	When this method returns contains the content of the variable coded in the response parameters if the conversion succeeded, or the null if the conversion failed.
	* @param ex	Exception to be thrown when extraction fails
	* @return true if extraction succeeded, false otherwise
	*/
	protected: virtual bool xtractData(const Response& response, std::string& variableData, Exception& ex) const;

   /**
   * Request the update of the value of a variable in the Blackboard
   * @param timeout The amount of time to wait for a write confirmation from blackboard
   * @param value The new value for the variable
   * @param ex When this method returns contains null if the new variable data was written successfully, or the exception to be thrown if the write failed
   * @return true if the new variable data was written successfully, false otherwise
   */
	private: bool sendUpdatedSerializedData(const int& timeout, const T& value, Exception& ex);

	 /**
	 * Serializes the provided object to an array of bytes
	 * @param value The object to be serialized
	 * @returns The array of bytes obtained from serialization
	 */
	private: std::string serialize(const T& value);

	/**
	* Serializes the provided object to a string
	* @param value Object to be serialized
	* @param serializedData When this method returns contains value serialized if the serialization succeeded, or zero if the serialization failed. The serialization fails if the serializedData parameter is a null reference (Nothing in Visual Basic) or outside the specification for the type. This parameter is passed uninitialized
	* @returns true if value was serialized successfully; otherwise, false
	*/
	protected: virtual bool serialize(const T& value, std::string& serializedData) const = 0;

	/**
	* Gets the value stored in the blackboard for the SharedVariable represented by this object. A return value indicates whether the acquisition operation succeeded
	* @param value When this method returns, contains the value stored in the blackboard for the SharedVariable represented by this object, if the conversion succeeded, or the default value of the type if the conversion failed.
	* @returns true if the the data acquisition operation succeeded, false otherwise
	*/
	public: bool tryRead(T& value);

	/**
	* Gets the value stored in the blackboard for the SharedVariable represented by this object. A return value indicates whether the acquisition operation succeeded
	* @param value When this method returns, contains the value stored in the blackboard for the SharedVariable represented by this object, if the conversion succeeded, or the default value of the type if the conversion failed.
	* @param timeout The amout of time to wait for a read confirmation from blackboard
	* @returns true if the the data acquisition operation succeeded, false otherwise
	*/
	public: bool tryRead(T& value, const int& timeout);

	/**
	* Writes the provided value to the blackboard variable associated to this SharedVariable object. A return value indicates whether the write operation succeeded
	* @param value The value to write in to the blackboard shared variable
	* @return true if the the data write operation succeeded, false otherwise
	*/
	public: bool tryWrite(const T& value);
	/**
	* Writes the provided value to the blackboard variable associated to this SharedVariable object. A return value indicates whether the write operation succeeded
	* @param value The value to write in to the blackboard shared variable
	* @param timeout The amount of time to wait for a write confirmation from blackboard. Use Zero to write without wait for confirmation. Use -1 to wait indefinitely
	* @return true if the the data write operation succeeded, false otherwise
	*/
	public: bool tryWrite(const T& value, const int& timeout);

	/**
	* Deserializes the provided data to an object of the type of the variable
	* @param data The data to be deserialized
	* @returns The object obtained from deserialization
	*/
	private: T deserialize(const std::string& data);

	/**
	* Deserializes the provided object from a string
	* @param serializedData String containing the serialized object
	* @param value When this method returns contains the value stored in serializedData the deserialization succeeded, or zero if the deserialization failed. The deserialization fails if the serializedData parameter is a null reference (Nothing in Visual Basic) or its content could not be parsed. This parameter is passed uninitialized
	* @returns true if serializedData was deserialized successfully; otherwise, false
	*/
	protected: virtual bool deserialize(const std::string& serializedData, T& value) const = 0;

	protected: void onWriteNotification(const SharedVariableSubscriptionReport<T>& report);
};

template <class T>
SharedVariableGeneric<T>::SharedVariableGeneric(const std::string variableName):
initialized(false), variableName(variableName),
subscriptionReportType(SharedVariableReportType::Unknown), subscriptionType(SharedVariableSubscriptionType::Unknown){}

template <class T>
SharedVariableGeneric<T>::SharedVariableGeneric(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize):
initialized(false), variableName(variableName),
subscriptionReportType(SharedVariableReportType::Unknown), subscriptionType(SharedVariableSubscriptionType::Unknown){	
	//this->lastUpdate = DateTime.MinValue;
	//this->defaultValue = value;
	//this->serializer = new SharedVariableStringSerializer<T>(Serialize);
	//this->deserializer = new SharedVariableStringDeserializer<T>(Deserialize);
	T value = T();
	this->commandManager = commandManager;
	if ((commandManager != NULL) && initialize)
		this->initialize(value);
}

template <class T>
void SharedVariableGeneric<T>::setCommandManager(SimpleCommandManager* value){
	SharedVariable::setCommandManager(value);
	//initialize(this->defaultValue);
}

template <class T>
const bool SharedVariableGeneric<T>::getInitialized() const{
	return initialized;
}

template <class T>
const bool SharedVariableGeneric<T>::isArray() const{
	return false;
}

template <class T>
void SharedVariableGeneric<T>::initialize(){
	T instance = T();
	//if(isPointer<T>::value)
	//	instance = NULL;
	initialize(instance);
}
template <class T>
void SharedVariableGeneric<T>::initialize(T value){
	if (initialized || (commandManager == NULL))
		return;

	Exception ex;
	bool success;
	std::stringstream parameters;
	//int size;
	std::string data;
	T content;

	Command command("read_var", variableName);
	// Three initialization attempts
	success = false;
	Response *response = NULL;
	for (int i = 0; i < 3; ++i)
	{
		if (success = commandManager->sendAndWait(command, 300, response))
			break;
	}
	if (!success)
		return;

	// The variable exists and is responding
	if (response->success)
	{
		initialized = true;
		if (!xtractData(*response, data, ex))
			throw ex;
		if (!deserialize(data, content))
		{
			ex = Exception("Deserialization error with string: " + data);
			throw ex;
		}
		updateInfo();
		setBufferedData(content);
		delete response;
		return;
	}

	// The variable does not exist. Try to create a new one
	//if (typeof(T).IsValueType)
	//{
	//	DecodeData(default(T), out data);
	//	size = data.Length;
	//}
	//else size = 0;
	//size = 0;

	parameters << "{ " << getTypeName();
	if (isArray())
	{
		parameters << "[";
		if (getLength() != -1)
			parameters << getLength();
		parameters << "]";
	}
	parameters << " " << variableName << " }";
	command = Command("create_var", parameters.str());
	delete response;
	if (!commandManager->sendAndWait(command, 300, response))
		throw Exception("Can not create variable in blackboard");
	tryWrite(value);
	updateInfo();
	initialized = true;
	delete response;
}

template <class T>
const std::string& SharedVariableGeneric<T>::getLastWriter() const {
	return this->lastWriter;
}

template <class T>
void SharedVariableGeneric<T>::setLastWriter(const std::string& value) {
	this->lastWriter = std::string(value);
}

template <class T>
const int SharedVariableGeneric<T>::getLength() const{
	return -1;
}

template <class T>
const std::string SharedVariableGeneric<T>::getTypeName() const{
	return "var";
}

template <class T>
const std::string SharedVariableGeneric<T>::getName() const{
	return variableName;
}

template <class T>
const T& SharedVariableGeneric<T>::getBufferedData(){
	return bufferedData;
}

template <class T>
void SharedVariableGeneric<T>::setBufferedData(const T& value){
	previousBufferedData = bufferedData;
	bufferedData = value;
}

template <class T>
const SharedVariableReportType& SharedVariableGeneric<T>::getSubscriptionReportType(){
	return this->subscriptionReportType;
}

template <class T>
void SharedVariableGeneric<T>::setSubscriptionReportType(const SharedVariableReportType& value){
	this->subscriptionReportType = value;
}

template <class T>
const SharedVariableSubscriptionType& SharedVariableGeneric<T>::getSubscriptionType(){
	return this->subscriptionType;
}

template <class T>
void SharedVariableGeneric<T>::setSubscriptionType(const SharedVariableSubscriptionType& value){
	this->subscriptionType = value;
}

template <class T>
bool SharedVariableGeneric<T>::getUpdatedSerializedData(const int& timeout, std::string& serializedData, Exception& ex)
{
	serializedData = std::string();
	Command cmdReadVar("read_var", variableName);
	Response *rspReadVar = NULL;
	if (!commandManager->sendAndWait(cmdReadVar, timeout, rspReadVar))
	{
		ex = Exception("No response from blackboard");
		return false;
	}
	if (!(rspReadVar->success))
	{
		ex = Exception("Cannot read variable" + variableName);
		delete rspReadVar;
		return false;
	}
	
	if (!xtractData(*rspReadVar, serializedData, ex))
	{
		delete rspReadVar;
		return false;
	}
	delete rspReadVar;
	return true;
}

template <class T>
T SharedVariableGeneric<T>::read(){
	Exception ex;
	T value;
	if (!read(value, 300, ex))
		throw ex;
	return value;
}

template <class T>
T SharedVariableGeneric<T>::read(const int& timeout){
	Exception ex;
	T value;
	if (!read(value, timeout, ex))
		throw ex;
	return value;
}

template <class T>
bool SharedVariableGeneric<T>::read(T& value, const int& timeout, Exception& ex)
{
	if (commandManager == NULL)
	{
		ex = Exception("Cannot communicate with blackboard");
		return false;
	}

	std::string data;
	if (!getUpdatedSerializedData(timeout, data, ex))
		return false;

	return updateValue(data, value, ex);
}

template <class T>
void SharedVariableGeneric<T>::write(const T& value)
{
	Exception ex;
	if (!write(value, 300, ex))
		throw ex;
}

template <class T>
void SharedVariableGeneric<T>::write(const T& value, const int& timeout)
{
	Exception ex;
	if (!write(value, timeout, ex))
		throw ex;
}

template <class T>
bool SharedVariableGeneric<T>::write(const T& value, const int& timeout, Exception& ex)
{
	if (commandManager == NULL)
	{
		ex = Exception("Cannot communicate with blackboard");
		return false;
	}

	if (!sendUpdatedSerializedData(timeout, value, ex))
		return false;
	setBufferedData(value);
	//this->lastUpdate = DateTime.Now;
	//OnUpdated();
	return true;
}


template <class T>
bool SharedVariableGeneric<T>::xtractData(const Response& response, std::string& variableData, Exception& ex) const{
	std::string variableType;
	bool isArray;
	int arrayLength;
	std::string variableName;

	variableData.clear();
	if (!parseResponse(response, variableType, isArray, arrayLength, variableName, variableData))
	{
		ex = Exception("Response parameters has an invalid format");
		return false;
	}
	if (this->variableName.compare(variableName) != 0)
	{
		ex = Exception("Variable name mismatch");
		return false;
	}
	if (this->getTypeName().compare(variableType) != 0)
	{
		ex = Exception("Variable type mismatch");
		return false;
	}
	return true;
}


template <class T>
void SharedVariableGeneric<T>::subscribe(SharedVariableReportType reportType, 
										 SharedVariableSubscriptionType subscriptionType, 
										 const int& timeout, const int& attempts){
	if (this->commandManager == NULL)
		throw new Exception("Cannot communicate with blackboard");

	std::string sType;
	std::string rType;
	std::stringstream parameters;
	bool success;
	int count;

	switch (subscriptionType)
	{
		case SharedVariableSubscriptionType::None:
			throw Exception("Invalid SharedVariableSubscriptionType value");
			//Unsubscribe();
			//return;

		case SharedVariableSubscriptionType::Unknown:
			throw Exception("Invalid SharedVariableSubscriptionType value");

		case SharedVariableSubscriptionType::Creation:
			sType = "creation";
			break;

		case SharedVariableSubscriptionType::WriteAny:
			sType = "writeany";
			break;

		case SharedVariableSubscriptionType::WriteOthers:
			sType = "writeothers";
			break;

		case SharedVariableSubscriptionType::WriteModule:
			sType = "writemodule";
			throw Exception("Unsupported option");
			//break;

		default:
			sType = "writeothers";
			subscriptionType = SharedVariableSubscriptionType::WriteOthers;
			break;
	}

	switch (reportType)
	{
		case SharedVariableReportType::None:
			throw Exception("Invalid SharedVariableReportType value");
			//Unsubscribe();
			//return;

		case SharedVariableReportType::Unknown:
			throw Exception("Invalid SharedVariableReportType value");

		case SharedVariableReportType::SendContent:
			rType = "content";
			break;

		case SharedVariableReportType::Notify:
			rType = "notify";
			break;

		default:
			rType = "notify";
			break;
	}

	parameters << variableName << " subscribe=" << sType << " report=" << rType;

	Command cmdSubscribe("subscribe_var", parameters.str());
	Response *rspSubscribe;
	success = false;
	count = 0;
	do
	{
		++count;
		if (!commandManager->sendAndWait(cmdSubscribe, timeout, rspSubscribe))
			continue;
		success = rspSubscribe->success;
		if(rspSubscribe != NULL)
			delete rspSubscribe;
	} while (!success && (count < attempts));

	if (!success)
	{
		if (rspSubscribe == NULL)
			throw Exception("No response from blackboard");
		throw Exception("Subscription failed");
	}
	this->subscriptionReportType = reportType;
	this->subscriptionType = subscriptionType;
}

template <class T>
void SharedVariableGeneric<T>::unsubscribe(const int& timeout, const int& attempts){
	if (this->commandManager == NULL)
		throw Exception("Cannot communicate with blackboard");
	 
	bool success;
	int count;

	Command cmdUnsubscribe("unsubscribe_var", variableName);
	Response *rspUnsubscribe;
	success = false;
	count = 0;
	do
	{
		++count;
		rspUnsubscribe = NULL;
		if (!commandManager->sendAndWait(cmdUnsubscribe, timeout, rspUnsubscribe))
			continue;
		success = rspUnsubscribe->success;
		if((rspUnsubscribe != NULL) && !success)
			delete rspUnsubscribe;
	} while (!success && (count < attempts));

	delete rspUnsubscribe;
	if (!success)
	{
		if (rspUnsubscribe == NULL)
			throw Exception("No response from blackboard");
		throw Exception("Subscription removal failed");
	}
	this->subscriptionType = SharedVariableSubscriptionType::None;
	this->subscriptionReportType = SharedVariableReportType::None;
}

template <class T>
bool SharedVariableGeneric<T>::updateBufferedData(const int& timeout){
	T value;
	return tryRead(value, timeout);
}

template <class T>
bool SharedVariableGeneric<T>::update(const SharedVariableReport& svReport, Exception& ex){
	onReportReceived(svReport);
	if (!isValidUpdateData(svReport.getVariableInfo()->getTypeName(),
		svReport.getVariableInfo()->isArray(),
		svReport.getVariableInfo()->getLength(),
		svReport.getVariableInfo()->getName(), ex))
		return false;

	T value;
	const T& oldValue = getBufferedData();
	if (!updateValue(svReport.getSerializedData(), svReport.getWriter(), value, ex))
		return false;

	SharedVariableSubscriptionReport<T> report(this, svReport.getReportType(), svReport.getSubscriptionType(), svReport.getWriter(), value);
	onWriteNotification(report);

	// // Check if value changed
	// IComparable<T> cValue = value as IComparable<T>;
	// if((cValue != null) && (cValue.CompareTo(oldValue) != 0))
	//	OnValueChanged(report);
	// else if(!System.Collections.Generic.EqualityComparer<T>.Default.Equals(oldValue, value))
	//	OnValueChanged(report);
	return true;
}

template <class T>
bool SharedVariableGeneric<T>::updateValue(const std::string& serializedData, T& value, Exception& ex){
	return updateValue(serializedData, std::string(), value, ex);
}

template <class T>
bool SharedVariableGeneric<T>::updateValue(const std::string& serializedData, const std::string& writerModuleName, Exception& ex){
	T value = T();
	//if(isPointer<T>::value)
	//	value = NULL;
	return updateValue(serializedData, writerModuleName, value, ex);
}

template <class T>
bool SharedVariableGeneric<T>::updateValue(const std::string& serializedData, const std::string& writerModuleName, T& value, Exception& ex){
	try
	{
		value = deserialize(serializedData);
		this->setLastWriter(writerModuleName);
		this->setBufferedData(value);
		//this.lastUpdate = DateTime.Now;
	}
	catch (Exception dex)
	{
		ex = dex;
		return false;
	}
	//OnUpdated();
	return true;
}

template <class T>
bool SharedVariableGeneric<T>::sendUpdatedSerializedData(const int& timeout, const T& value, Exception& ex){
	std::stringstream sParams;
	std::string data;

	if (!serialize(value, data))
	{
		ex = Exception("Serialization error.");
		return false;
	}

	sParams << "{ " << getTypeName();
	if (isArray()){
		if(getLength() >= 0)
			sParams << "[" << getLength() << "]";
		else
			sParams << "[]";
	}
	sParams << " " << variableName << " " << data << " }";

	Command cmdWriteVar = Command("write_var", sParams.str());
	
	Response *rspWriteVar;
	if (timeout != 0)
	{
		if (!commandManager->sendAndWait(cmdWriteVar, timeout, rspWriteVar))
		{
			ex = Exception("No response from blackboard");
			return false;
		}
		if (!rspWriteVar->success)
		{
			ex = Exception("Cannot write variable" + variableName);
			delete rspWriteVar;
			return false;
		}
	}
	else if (!commandManager->send(cmdWriteVar))
	{
		ex = Exception("Cannot write variable" + variableName);
		return false;
	}

	return true;
}

template <class T>
std::string SharedVariableGeneric<T>::serialize(const T& value){
	std::string serializedData;
	if (!serialize(value, serializedData))
		throw Exception("Serialization error.");
	return serializedData;
}

template <class T>
bool SharedVariableGeneric<T>::tryRead(T& value){
	Exception ex;
	return read(value, 300, ex);
}

template <class T>
bool SharedVariableGeneric<T>::tryRead(T& value, const int& timeout){
	Exception ex;
	return read(value, timeout, ex);
}

template <class T>
T SharedVariableGeneric<T>::deserialize(const std::string& data)
{
	T value;
	if (!deserialize(data, value))
		throw Exception("Deserialization error.");
	return value;
}

template <class T>
void SharedVariableGeneric<T>::onWriteNotification(const SharedVariableSubscriptionReport<T>& report){
	writeNotification(report);
}


template <class T>
bool SharedVariableGeneric<T>::tryWrite(const T& value)
{
	Exception ex;
	return write(value, 300, ex);
}

template <class T>
bool SharedVariableGeneric<T>::tryWrite(const T& value, const int& timeout)
{
	Exception ex;
	return write(value, timeout, ex);
}

#endif // __SHARED_VARIABLE_GENERIC_H__
