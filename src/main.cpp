// Include standard libraries
#include <cstdlib>
#include <iostream>
#include <string>

// Audio & voice
#include <festival.h>
#define FEST_DEFAULT_HEAP_SIZE 2100000  // default scheme heap size
#include "Misc.h"
#include "SoundEngine.h"

// uRobotics
// Class that manages connection with Blackboard
#include <uRobotics/api/SimpleConnectionManager.h>
// Class that manages commands and shared variables
#include <uRobotics/api/SimpleCommandManager.h>
// Class that encapsulates a command
#include <uRobotics/api/Command.h>
// Class that encapsulates a response
#include <uRobotics/api/Response.h>
// Exception handling
#include <uRobotics/Exception.h>

// Local command executers used to execute commands received from blackboard
#include "command_executers/Say.h"
#include "command_executers/Read.h"
#include "command_executers/ASay.h"
#include "command_executers/ARead.h"
// #include "PlayCommandExecuter.h"

using voice::SoundEngine;
using voice::SpeechGenerator;

void setupAudio(SpeechGenerator*& speechGenerator, SoundEngine*& soundEngine);

int main(int argc, char** argv){
	// Create and initialize managers
	SimpleCommandManager cmdMan;
	SimpleConnectionManager cnnMan(2052);
	cmdMan.bindConnectionManager(cnnMan);

	// Setup audio engines
	SoundEngine* soundEngine;
	SpeechGenerator* speechGenerator;
	setupAudio(speechGenerator, soundEngine);

	// Setup command executers
	cmdMan.getCommandExecuters().add(new voice::command_executers::Say(speechGenerator));
	cmdMan.getCommandExecuters().add(new voice::command_executers::ASay(speechGenerator));
	cmdMan.getCommandExecuters().add(new voice::command_executers::Read(speechGenerator));
	cmdMan.getCommandExecuters().add(new voice::command_executers::ARead(speechGenerator));
	// cmdMan.getCommandExecuters().add(new PlayCommandExecuter());

	// Start engine
	std::cout << "Starting SP-GEN in  port" << cnnMan.getPort() << std::endl;
	cmdMan.start();
	std::cout << "Waiting for Blackboard" << std::endl;
	cnnMan.waitClientConnected();
	std::cout << "Loading shared variables" << std::endl;
	cmdMan.getSharedVariables().loadFromBlackboard();
	cmdMan.setReady(true);
	std::cout << "Ready!" << std::endl << std::endl;

	// Run
	while(true)
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));

	return -1;
}

/**
* Sets up the audio engines
*/
void setupAudio(SpeechGenerator*& speechGenerator, SoundEngine*& soundEngine){

	// Misc::linuxRun("pulseaudio -k");
	try{
		speechGenerator = new SpeechGenerator();
		// soundEngine = new SoundEngine();
	}
	catch( const Robotics::Exception& ex ){
		std::cerr << "Error setting up engines: " << ex.what() << std::endl;
		std::exit(-1);
	}
	catch( const std::exception& ex ){
		std::cerr << "Error setting up engines: " << ex.what() << std::endl;
		std::exit(-1);
	}
	catch( ... ){
		std::cerr << "Unknown error while setting up engines." << std::endl;
		std::exit(-1);
	}
}