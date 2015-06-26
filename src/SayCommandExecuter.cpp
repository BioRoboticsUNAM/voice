#include "SayCommandExecuter.h"

#include <cstdlib>
#include <string>
#include <sstream>

// uRobotics
#include <uRobotics/Exception.h>

using namespace Robotics;

// In the constructor may be defined the name of the command this command executer manages
SayCommandExecuter::SayCommandExecuter(const SpeechGenerator* speechGenerator) :
AsyncCommandExecuter("say"), spGen(speechGenerator){
	if(speechGenerator == NULL)
		throw Exception("speechGenerator cannot be NULL");
	spGen = speechGenerator;
}

SayCommandExecuter::~SayCommandExecuter(void){}

bool SayCommandExecuter::parametersRequired() const{
	return true;
}

Response* SayCommandExecuter::AsyncTask(const Command& command){

	std::cout << "Saying: \"" << command.parameters << "\"... ";
	bool result = spGen->speak(command.parameters);
	std::cout << (result ? "Done!" : "Failed!!!") << std::endl;
	return Response::createFromCommand(command, result);
}