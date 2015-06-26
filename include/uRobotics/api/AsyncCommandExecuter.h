/* 
 * File:   AsyncCommandExecuter.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#pragma once
#ifndef __ASYNC_COMMAND_EXECUTER_H__
#define	__ASYNC_COMMAND_EXECUTER_H__

#include <string>
#include <sstream>
#include <boost/thread.hpp>
#include "Command.h"
#include "Response.h"
#include "CommandExecuter.h"

class AsyncCommandExecuter : public CommandExecuter
{
private:
	bool busy;
	bool running;
	boost::thread *asyncExecutionThread;

public:

public:
	AsyncCommandExecuter(const std::string& commandName);
	AsyncCommandExecuter(const std::string& commandName, SimpleCommandManager *cmdMan);
	virtual ~AsyncCommandExecuter(void);

	bool abort();
	void execute(const Command& cmd);
	virtual bool isBusy() const;
	virtual bool isRunning() const;
	virtual bool parametersRequired() const;

	virtual Response* AsyncTask(const Command& command) = 0;

private:
	void asyncExecutionThreadTask(const Command& command);
};

#endif // __ASYNC_COMMAND_EXECUTER_H__