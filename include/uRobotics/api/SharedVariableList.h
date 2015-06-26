#ifndef __SHARED_VARIABLE_LIST_H__
#define __SHARED_VARIABLE_LIST_H__

#include <string>
#include <map>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <uRobotics/api/SharedVariable.h>
#include "Response.h"

class SimpleCommandManager;

class SharedVariableList
{
private:
	SharedVariableList(void);
	SharedVariableList(const SharedVariableList& other);
	SimpleCommandManager& commandManager;
	std::map<std::string, SharedVariable*> sharedVariableList;
	/**
	* Mutex for the Command executer list
	*/
	boost::interprocess::interprocess_mutex sharedVariableListMutex;	

public:
	~SharedVariableList(void);

	/**
	* Initializes a new instance of SharedVariableList
	* @param commandManager The CommandManager object this List will be bound to
	*/
	SharedVariableList(SimpleCommandManager& commandManager);

	/**
	* Adds an item to the SharedVariableList.
	* @param item The SharedVariable object to add to the SharedVariableList.
	*/
	void add(SharedVariable* item);

	/**
	* Removes all items from the SharedVariableList.
	*/
	void clear();

	/**
	* Determines whether the SharedVariableList contains a specific value.
	* @param variableName The name of the SharedVariable object to locate in the SharedVariableList.
	* @return true if item is found in the IList; otherwise, false
	*/
	bool contains(const std::string& variableName) const;

	/**
	* Gets the number of elements actually contained in the SharedVariableList. 
	*/
	int count() const;

	/**
	* Fills the list with all the variables from the blackboard
	* @return The number of loaded variables
	*/
	int loadFromBlackboard();

	/**
	* Fills the list with all the variables from the blackboard
	* @param timeout Data request timeout
	* @param message When this method returns contains any error message produced
	* @return The number of loaded variables
	*/
	int loadFromBlackboard(const int& timeout, std::string& message);

	/**
	* Removes the item at the specified index
	* @param index The zero-based index of the item to remove.
	*/
	void removeAt(const int& index);

	/**
	* Removes the SharedVariable object from the SharedVariableList.
	* @param variableName The name of the shared variable to remove from the SharedVariableList.
	* @return true if item was successfully removed from the SharedVariableList; otherwise, false. This method also returns false if item is not found in the original SharedVariableList
	*/
	bool remove(const std::string& variableName);
	/**
	* Updates the list of shared variables with the missing variables from the blackboard
	* @return The number of loaded variables
	*/
	// internal
	int updateFromBlackboard(const Response& response);
	/**
	* Updates the list of shared variables with the missing variables from the blackboard
	* @return The number of loaded variables
	*/
	// internal
	int updateFromBlackboard(const Response& response, std::string& message);
	SharedVariable* operator[](const std::string& variableName);

private:
	/**
	* Registers an existing variable within the list
	* @param type The type of the variable to register
	* @param isArray Indicates if the variable is an array
	* @param name The name of the variable to register
	* @param data The data of the variable to register received in the read operation
	*/
	bool registerVar(std::string type, bool isArray, std::string name, std::string data);
	/**
	* Splits a string containing multiple shared variables into each shared variable
	* @param s String to split
	* @return Array of each shared variable in string format
	*/
	static std::vector<std::string> splitMultipleSharedVariables(const std::string& s);
};

#endif // __SHARED_VARIABLE_LIST_H__

