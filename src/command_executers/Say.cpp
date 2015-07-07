#include "Say.h"

#include <cstdlib>
#include <string>
#include <sstream>

// uRobotics
#include <uRobotics/Exception.h>

using voice::SpeechGenerator;
using voice::command_executers::Say;
using Robotics::Exception;

Say::Say(const SpeechGenerator* speechGenerator, const std::string& commandName)
	: AsyncCommandExecuter(commandName), spGen(speechGenerator){
	if(speechGenerator == NULL)
		throw Exception("speechGenerator cannot be NULL");
	spGen = speechGenerator;
}

Say::~Say(void){}

bool Say::parametersRequired() const{
	return true;
}

Response* Say::AsyncTask(const Command& command){

	std::cout << "Saying: \"" << command.parameters << "\"... ";
	bool result = spGen->speak(command.parameters);
	std::cout << (result ? "Done!" : "Failed!!!") << std::endl;
	return Response::createFromCommand(command, result);
}