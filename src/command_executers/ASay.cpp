#include "ASay.h"

#include <cstdlib>
#include <string>
#include <sstream>

// uRobotics
#include <uRobotics/Exception.h>

using voice::SpeechGenerator;
using voice::command_executers::ASay;
using Robotics::Exception;

ASay::ASay(const SpeechGenerator* speechGenerator, const std::string& commandName)
	: AsyncCommandExecuter(commandName), spGen(speechGenerator){
	if(speechGenerator == NULL)
		throw Exception("speechGenerator cannot be NULL");
	spGen = speechGenerator;
}

ASay::~ASay(void){}

bool ASay::parametersRequired() const{
	return true;
}

Response* ASay::AsyncTask(const Command& command){

	std::cout << "Enqueued: \"" << command.parameters << "\"... ";
	spGen->speakAsync(command.parameters);
	return Response::createFromCommand(command, true);
}