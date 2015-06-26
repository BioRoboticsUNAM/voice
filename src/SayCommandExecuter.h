/* 
 * File:   SayCommandExecuter.h
 * Author: Mauricio Matamoros
 *
 * There are two kinds of command executers: SyncCommandExecuter and AsyncCommandExecuter.
 * SyncCommandExecuter: those are executed within the CommandManager's main thread context, they do not allow communications and shall return in a few milliseconds
 * AsyncCommandExecuter: those are executed in a separate thread, allow communications and may take long periods of time to execute.
 */

#ifndef __SAY_COMMAND_EXECUTER_H__
#define	__SAY_COMMAND_EXECUTER_H__

#include "SpeechGenerator.h"

#include <uRobotics/api/Command.h>
#include <uRobotics/api/Response.h>
#include <uRobotics/api/AsyncCommandExecuter.h>

class SayCommandExecuter : public AsyncCommandExecuter
{
public:
	SayCommandExecuter(const SpeechGenerator* speechGenerator);
	~SayCommandExecuter(void);
	// This method indicates if the command executer requires parameters or not. It is recommended to be overloaded
	virtual bool parametersRequired() const;
	// This method executes the command. It must be overloaded
	virtual Response* AsyncTask(const Command& command);

private:
	const SpeechGenerator* spGen;
	SayCommandExecuter(void);
	SayCommandExecuter(const SayCommandExecuter&);
};



#endif // __SAY_COMMAND_EXECUTER_H__