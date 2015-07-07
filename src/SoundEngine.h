#pragma once
#ifndef __SOUND_ENGINE_H__
#define __SOUND_ENGINE_H__

#include <string>
#include <sndfile.h>
#include <portaudio.h>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include <uRobotics/Exception.h>

namespace voice{
	class PlayJob;

	class SoundEngine{
	private:
		PaStreamParameters *out;
		boost::mutex playLock;

		SoundEngine(const SoundEngine& other);
		void initialize();

	public:
		SoundEngine();
		virtual ~SoundEngine();

		bool initialized() const;
		bool tryPlayFile(const std::string& filePath);
		bool tryPlayFile(const std::string& filePath, Robotics::Exception& ex);
	};
}
#endif // __SOUND_ENGINE_H__
