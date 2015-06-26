/* 
 * File:   SimpleCommandManager.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#ifndef __SIMPLE_COMMAND_MANAGER_H__
#define	__SIMPLE_COMMAND_MANAGER_H__

#include <cstdlib>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>
#include "uRobotics/utilities/ProducerConsumer.h"
#include "Command.h"
#include "Response.h"
#include "SimpleConnectionManager.h"
#include "CommandExecuterCollection.h"
#include "SharedVariableList.h"

using namespace Robotics::Utilities;
typedef boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> scoped_lock;

class SimpleCommandManager {
private:
	bool running;
	bool busy;
	bool ready;
	boost::thread* mainThread;
	boost::thread* parserThread;
	boost::thread* responseAnalizerThread;
	SimpleConnectionManager* cnnMan;
	/**
	* Queue of received commands.
	*/
	ProducerConsumer<Command*> commandsReceived;
	/**
	* Queue of received responses.
	*/
	ProducerConsumer<Response*> responsesReceived;
	/**
	* List of received responses which has not been paired with a sent command
	*/
	std::vector<Response*> unpairedResponses;
	boost::interprocess::interprocess_mutex unpairedResponsesMutex;	
	CommandExecuterCollection executers;
	SharedVariableList sharedVariables;

public:
	SimpleCommandManager();
	virtual ~SimpleCommandManager();
	bool isRunning();
	bool getBusy();
	void setBusy(bool busy);
	bool getReady();
	void setReady(bool ready);
	CommandExecuterCollection& getCommandExecuters();
	void bindConnectionManager(SimpleConnectionManager& cnnMan);
	SimpleConnectionManager& getConnectionManager();
	SharedVariableList& getSharedVariables();
	void start();
	void stop();
	bool send(const Command& command);
	bool send(const Response& response);
	bool sendAndWait(const Command& command, const int& timeout, Response*& response);
	boost::signals2::signal<void(const SimpleCommandManager*)> sharedVariablesLoaded;

protected:
	/**
	* Manages the events of the shared variables
	* @param response Response which contains a the shared variable data
	*/
	bool manageSubscription(const Response& response);
	Response* waitForResponse(const Command& commandSent, const int& timeout);
	void cleanBuffers();
	void onSharedVariablesLoaded();

private:
	void mainThreadTask();
	void parserThreadTask();
	void responseAnalizerThreadTask();
	void parseTcpPacket(TcpPacket& packet);
	void executeCommand(const Command& command);
	bool executeSystemCommand(const Command& command);
};

#endif /* __SIMPLE_COMMAND_MANAGER_H__ */
