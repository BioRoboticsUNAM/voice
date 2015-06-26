/* 
 * File:   SpeechTask.h
 * Author: Mauricio Matamoros
 */

#ifndef __SPEECH_TASK_H__
#define	__SPEECH_TASK_H__

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

class SpeechTask{
public:
	SpeechTask(const std::string& textToSynth);
	~SpeechTask();
	bool complete;
	const char* getText() const;
	void wait();
	void signal();

private:
	SpeechTask();
	SpeechTask(const SpeechTask&);
	
private:
	std::string tts;
	boost::interprocess::interprocess_semaphore syncSem;
};


typedef boost::shared_ptr<SpeechTask> SpeechTaskPtr;

#endif // __SPEECH_TASK_H__