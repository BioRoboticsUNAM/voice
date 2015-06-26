/* 
 * File:   SpeechGenerator.h
 * Author: Mauricio Matamoros
 */

#ifndef __SPEECH_GENERATOR_H__
#define	__SPEECH_GENERATOR_H__
#define FEST_DEFAULT_HEAP_SIZE 2100000  // default scheme heap size

#include "SpeechTask.h"

#include <string>
#include <boost/thread.hpp>

// uRobotics
#include <uRobotics/utilities/ProducerConsumer.h>

using namespace Robotics::Utilities;

class SpeechGenerator
{
public:
	SpeechGenerator(void);
	virtual ~SpeechGenerator(void);
	bool speak(const std::string& textToSynth) const;
	void speakAsync(const std::string& textToSynth) const;

private:
	static ProducerConsumer<SpeechTaskPtr> speechTasks;
	static boost::thread* speechThread;
	static void speechThreadTask();
	SpeechGenerator(const SpeechGenerator&);
};

#endif // __SPEECH_GENERATOR_H__