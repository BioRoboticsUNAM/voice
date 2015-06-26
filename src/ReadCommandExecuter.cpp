#include "ReadCommandExecuter.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <streambuf>

// uRobotics
#include <uRobotics/Exception.h>

using namespace Robotics;

void readAllText(const std::string& filePath, std::string& text);

// In the constructor may be defined the name of the command this command executer manages
ReadCommandExecuter::ReadCommandExecuter(const SpeechGenerator* speechGenerator) :
AsyncCommandExecuter("read"){
	if(speechGenerator == NULL)
		throw Exception("speechGenerator cannot be NULL");
	spGen = speechGenerator;
}

ReadCommandExecuter::~ReadCommandExecuter(void){}

bool ReadCommandExecuter::parametersRequired() const{
	return true;
}

Response* ReadCommandExecuter::AsyncTask(const Command& command){
	std::string tts;

	readAllText(command.parameters, tts);
	bool result = spGen->speak(tts);
	return Response::createFromCommand(command, result);
}

void readAllText(const std::string& filePath, std::string& text){

	try{
		std::ifstream fs(filePath.c_str());

		fs.seekg(0, std::ios::end);   
		text.reserve(fs.tellg());
		fs.seekg(0, std::ios::beg);

		text.assign(
			(std::istreambuf_iterator<char>(fs)),
			std::istreambuf_iterator<char>()
		);
	}
	catch( const std::exception& ex ){
		std::cerr << "Error reading file " << filePath << " : " << ex.what() << std::endl;
	}
	catch( ... ){ std::cerr << "Error reading file " << filePath << std::endl; }
}