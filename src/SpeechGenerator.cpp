#include "SpeechGenerator.h"

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