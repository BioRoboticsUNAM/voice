/* 
 * File:   SyncCommandExecuter.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#pragma once
#ifndef __SYNC_COMMAND_EXECUTER_H__
#define	__SYNC_COMMAND_EXECUTER_H__

#include <string>
#include <sstream>
#include "Command.h"
#include "Response.h"
#include "CommandExecuter.h"

class SyncCommandExecuter : public CommandExecuter
{
private:
	bool busy;
	bool running;

public:
	SyncCommandExecuter(const std::string& commandName);
	SyncCommandExecuter(const std::string& commandName, SimpleCommandManager *cmdMan);
	virtual ~SyncCommandExecuter(void);

	bool abort();
	void execute(const Command& cmd);
	virtual bool isBusy() const;
	virtual bool isRunning() const;
	virtual bool parametersRequired() const;
	
protected:
	virtual Response* SyncTask(const Command& command) = 0;

};

#endif // __SYNC_COMMAND_EXECUTER_H__