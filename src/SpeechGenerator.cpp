#include "SpeechGenerator.h"
#include <fstream>
#include <streambuf>

// Festival
#include <festival.h>

// uRobotics
#include <uRobotics/Exception.h>

using voice::SpeechTask;
using voice::SpeechTaskPtr;
using voice::SpeechGenerator;
using Robotics::Utilities::ProducerConsumer;


ProducerConsumer<SpeechTaskPtr> SpeechGenerator::speechTasks;
boost::thread* SpeechGenerator::speechThread = 
	new boost::thread(boost::bind(&SpeechGenerator::speechThreadTask));

SpeechGenerator::SpeechGenerator(void){
}

SpeechGenerator::SpeechGenerator(const SpeechGenerator&){}

SpeechGenerator::~SpeechGenerator(void){}

bool SpeechGenerator::read(const std::string& filePath) const{
	std::string tts;
	SpeechGenerator::readAllText(filePath, tts);
	return SpeechGenerator::speak(tts);
}

void SpeechGenerator::readAsync(const std::string& filePath) const{
	std::string tts;
	SpeechGenerator::readAllText(filePath, tts);
	SpeechGenerator::speakAsync(tts);
}

bool SpeechGenerator::speak(const std::string& tts) const{
	SpeechTaskPtr task(new SpeechTask(tts));
	SpeechGenerator::speechTasks.produce(task);
	task->wait();
	return task->complete;
}

void SpeechGenerator::speakAsync(const std::string& tts) const{
	SpeechTaskPtr task(new SpeechTask(tts));
	SpeechGenerator::speechTasks.produce(task);
}

void SpeechGenerator::speechThreadTask(){
	festival_initialize(1, FEST_DEFAULT_HEAP_SIZE);

	while(true){
		SpeechTaskPtr task = SpeechGenerator::speechTasks.consume();
		if(task == NULL) continue;

		try{
			festival_say_text(task->getText());
			task->complete = true;
		}
		catch( const std::exception& ex ){
			std::cerr <<
				"Error while trying to synthesize" << 
				task->getText() << " : " << ex.what() << std::endl;
		}
		catch( ... ){
			std::cerr << "Error while trying to synthesize: unknown"  << std::endl;
		}

		task->signal();
	}
}

void SpeechGenerator::readAllText(const std::string& filePath, std::string& text){

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