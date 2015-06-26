/* 
 * File:   SimpleCommandManager.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#pragma once
#ifndef __COMMAND_EXECUTER_COLLECTION_H__
#define	__COMMAND_EXECUTER_COLLECTION_H__

#include <string>
#include <map>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include "CommandExecuter.h"

typedef boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> scoped_lock;
class SimpleCommandManager;

class CommandExecuterCollection
{
private:
	/**
	* Stores the list of CommandExecuter sorted by the command name
	*/
	std::map<std::string, CommandExecuter*> commandExecuterList;
	/**
	* Mutex for the Command executer list
	*/
	boost::interprocess::interprocess_mutex commandExecuterListMutex;	
	/**
	* The CommandExecuter object to which this CommandExecuterCollection is bound to
	*/
	SimpleCommandManager& cmdMan;

	CommandExecuterCollection(const CommandExecuterCollection& other);
public:
	CommandExecuterCollection(SimpleCommandManager& cmdMan);
	~CommandExecuterCollection(void);
	/**
	* Gets the CommandManager object to which this CommandExecuterCollection is bound to
	*/
	SimpleCommandManager& getCommandManager() const;
	/**
	* Adds a CommandExecuter to the CommandExecuterCollection
	* @param commandExecuter The CommandExecuter to be added to the end of the CommandExecuterCollection.
	*/
	void add(CommandExecuter* commandExecuter);
	/**
	* Removes all elements from the CommandExecuterCollection
	*/
	void clear();
	/**
	* Determines whether an CommandExecuter is in the CommandExecuterCollection.
	* @param commandName The name of the command which represents the CommandExecuter to locate in the CommandExecuterCollection.
	* @returns true if the command asociated is found in the CommandExecuterCollection; otherwise, false
	*/
	bool contains(const std::string& commandName) const;
	/**
	* Removes the specified CommandExecuter from the CommandExecuterCollection
	* @param @commandExecuter The object to remove from the CommandExecuterCollection. The value can be a null reference (Nothing in Visual Basic) for reference types
	* @returns true if item is successfully removed; otherwise, false. This method also returns false if item was not found in the List
	*/
	int count();
	bool remove(const std::string& commandName);
	/**
	* Gets the CommandExecuter associated with the specified command name
	* @param commandName The name of the command managed by the CommandExecuter to get
	* @returns The CommandExecuter associated with the specified command name. If the specified command name is not found returns null
	*/
	CommandExecuter* operator[](const std::string& commandName);
};

#endif // __COMMAND_EXECUTER_COLLECTION_H__