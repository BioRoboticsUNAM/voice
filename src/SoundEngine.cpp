#include <sstream>
#include <iostream>
#include "SoundEngine.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>

// Only 2 channels will be accepted
#define    MAX_CHANNELS    2

using namespace Robotics;

SoundEngine::SoundEngine() : out(NULL){
	initialize();
}

SoundEngine::~SoundEngine(){
	if(out != NULL) Pa_Terminate();
}

bool SoundEngine::initialized() const{
	return (out != NULL) ? 1 : 0;
}

void SoundEngine::initialize(){
	boost::mutex::scoped_lock lock(playLock);
	PaError err = Pa_Initialize();
	if(err != paNoError) {
		out = NULL;
		std::stringstream ss;
		ss << "Error initializing PortAudio. Error code " << err;
		std::cerr << ss.str() << std::endl;
		throw Exception(ss.str());
		return;
	}

	out = new PaStreamParameters();
	if(out == NULL){
		std::stringstream ss;
		ss << "Error initializing PortAudio. Can't create stream parameters";
		std::cerr << ss.str() << std::endl;
		throw Exception(ss.str());
		return;
	}
	out->device = Pa_GetDefaultOutputDevice();
	if (out->device == paNoDevice) {
		std::stringstream ss;
		ss << "Error initializing PortAudio. No audio device";
		std::cerr << ss.str() << std::endl;
		throw Exception(ss.str());
		Pa_Terminate();
		delete out;
		out = NULL;
		return;
	}

	out->sampleFormat = paInt16;
	out->suggestedLatency = Pa_GetDeviceInfo(out->device)->defaultLowOutputLatency;
	out->hostApiSpecificStreamInfo = NULL;
}

bool SoundEngine::tryPlayFile(const std::string& filePath){
	Exception ex;
	return tryPlayFile(filePath, ex);
}

bool SoundEngine::tryPlayFile(const std::string& filePath, Exception& ex){
	SNDFILE *sfile;
	SF_INFO sfileInfo;
	PaStream *stream;
	short* buffer;
	unsigned long count;

	boost::mutex::scoped_lock lock(playLock);

	if( !initialized() ){
		ex = Exception("Uninitialized engine");
		return false;
	}

	sfile = sf_open (filePath.c_str(), SFM_READ, &sfileInfo);
	if (!sfile){
		ex = Exception("Cannot open file '" + filePath + "'");
		return false;
	}
	if (sfileInfo.channels > MAX_CHANNELS){
		std::stringstream msg;
		msg << "Unsupported number of channels (" << sfileInfo.channels << ")";
		ex = Exception(msg.str());
		return false;
	}

	out->channelCount = sfileInfo.channels;

	if (Pa_OpenStream(&stream,
						NULL,
						out,
						sfileInfo.samplerate,
						paFramesPerBufferUnspecified,
						paClipOff,
						NULL,
						NULL)
	!= paNoError ){
		ex = Exception("Cannot initialize stream");
		return false;
	}
	Pa_StartStream(stream);

	buffer = new short[1024];
	count = sf_read_short(sfile, buffer, 1024);
	while(count > 0){
		Pa_WriteStream( stream, buffer, count / sfileInfo.channels );
		count = sf_read_short(sfile, buffer, 1024);
	}
	delete[] buffer;

	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	sf_close(sfile);

	return true;
}
