#include "SpeechTask.h"

SpeechTask::SpeechTask(const std::string& textToSynth) 
: syncSem(0), tts(textToSynth), complete(false){}
SpeechTask::~SpeechTask(){
	this->syncSem.post();
}

const char* SpeechTask::getText() const{
	return this->tts.c_str();
}

void SpeechTask::signal(){
	this->syncSem.post();
}

void SpeechTask::wait(){
	this->syncSem.wait();
}