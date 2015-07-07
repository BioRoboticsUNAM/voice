#include "ARead.h"

#include <cstdlib>
#include <string>

// uRobotics
#include <uRobotics/Exception.h>

using Robotics::Exception;
using voice::SpeechGenerator;
using voice::command_executers::ARead;



ARead::ARead(const SpeechGenerator* speechGenerator, const std::string& commandName)
	: AsyncCommandExecuter(commandName){
	if(speechGenerator == NULL)
		throw Exception("speechGenerator cannot be NULL");
	spGen = speechGenerator;
}

ARead::~ARead(void){}

bool ARead::parametersRequired() const{
	return true;
}

Response* ARead::AsyncTask(const Command& command){
	std::string tts;

	spGen->readAsync(command.parameters);
	return Response::createFromCommand(command, true);
}