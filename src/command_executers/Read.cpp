#include "Read.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <streambuf>

// uRobotics
#include <uRobotics/Exception.h>

using Robotics::Exception;
using voice::SpeechGenerator;
using voice::command_executers::Read;

void readAllText(const std::string& filePath, std::string& text);

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