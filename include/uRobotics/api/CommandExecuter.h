/* 
 * File:   CommandExecuter.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#pragma once
#ifndef __COMMAND_EXECUTER_H__
#define	__COMMAND_EXECUTER_H__

#include <string>
#include <sstream>
#include "Command.h"
#include "Response.h"

class SimpleCommandManager;

class CommandExecuter
{
private:
	std::string commandName;
	SimpleCommandManager* cmdMan;

public:

public:
	CommandExecuter(const std::string& commandName);
	CommandExecuter(const std::string& commandName, SimpleCommandManager *cmdMan);
	virtual ~CommandExecuter(void);

	virtual bool isBusy() const = 0;
	virtual bool isRunning() const = 0;
	virtual bool parametersRequired() const = 0;
	virtual bool abort() = 0;
	virtual void execute(const Command& command) = 0;

	std::string getCommandName() const;
	SimpleCommandManager *getCmdMan() const;
	void setCmdMan(SimpleCommandManager *cmdMan);

protected:
	bool sendResponse(const Command& command, const bool& success) const;
	bool sendCommand(const Command& command) const;
	bool sendResponse(const Response& response) const;
};

#endif // __COMMAND_EXECUTER_H__