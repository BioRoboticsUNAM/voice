#include "Read.h"

#include <cstdlib>
#include <string>

// uRobotics
#include <uRobotics/Exception.h>

using Robotics::Exception;
using voice::SpeechGenerator;
using voice::command_executers::Read;



Read::Read(const SpeechGenerator* speechGenerator, const std::string& commandName)
	: AsyncCommandExecuter(commandName){
	if(speechGenerator == NULL)
		throw Exception("speechGenerator cannot be NULL");
	spGen = speechGenerator;
}

Read::~Read(void){}

bool Read::parametersRequired() const{
	return true;
}

Response* Read::AsyncTask(const Command& command){
	std::string tts;

	bool result = spGen->read(command.parameters);
	return Response::createFromCommand(command, result);
}