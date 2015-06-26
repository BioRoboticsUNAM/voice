#ifndef __RECOGNIZED_SPEECH_ALTERNATE_H__
#define __RECOGNIZED_SPEECH_ALTERNATE_H__

#include <string>

namespace Robotics{ namespace HAL{ namespace Sensors{

/**
* Represents a of Recognized Speech Alternate
*/
class RecognizedSpeechAlternate{

private:
	/**
	* The measure of certainty for a RecognizedSpeechAlternate
	*/
	float confidence;

	/**
	* The normalized text obtained by a recognition engine
	*/
	std::string text;

public:
	/**
	* Initializes a new instance of RecognizedSpeechAlternate
	* @param confidence The measure of certainty for a RecognizedSpeechAlternate
	* @param text The normalized text obtained by a recognition engine
	*/
	RecognizedSpeechAlternate(const std::string& text, const float& confidence);

	/**
	* Returns the measure of certainty for a RecognizedSpeechAlternate
	*/
	float getConfidence() const;

	/**
	* Returns the normalized text obtained by a recognition engine
	*/
	std::string getText() const;

	/**
	* Compares the current object with another object of the same type.
	* @param other An object to compare with this object.
	* @return A 32-bit signed integer that indicates the relative order of the objects being compared. The return value has the following meanings:
	* Less than zero -> This object is less than the other parameter.
	* Zero -> This object is equal to other.
	* Greater than zero -> This object is greater than other.
	*/
	int compareTo(const RecognizedSpeechAlternate& other);
	
protected:
	void setConfidence(const float& value) ;
	
	void setText(const std::string& value) ;
};

}/* Sensors */ } /* HAL */ } /* Robotics */

#endif // __RECOGNIZED_SPEECH_ALTERNATE_H__
