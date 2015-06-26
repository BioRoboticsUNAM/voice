#ifndef __RECOGNIZED_SPEECH_H__
#define __RECOGNIZED_SPEECH_H__

#include <string>
#include <vector>
#include <uRobotics/hal/sensors/RecognizedSpeechAlternate.h>

namespace Robotics{ namespace HAL{ namespace Sensors{

/**
* Represents a collection of Recognized Speech Alternates
*/
class RecognizedSpeech {
private:

	/**
	* The list of alternates
	*/
	std::vector<RecognizedSpeechAlternate*> alternates;
	
public:

	/**
	* Initializes a new instance of RecognizedSpeech
	*/
	RecognizedSpeech();

	/**
	* Gets the confidence of the alternate with highest confidence
	*/
	float getConfidence() const ;

	/**
	* Gets the number of elements contained in the Collection.
	*/
	int count() const ;

	/**
	* Gets a value indicating whether the Collection is read-only.
	*/
	bool isReadOnly() const ;

	/**
	* Gets the text of the alternate with highest confidence
	*/
	std::string getText() const ;

	/**
	* Gets the RecognizedSpeechAlternate with the specified index in the collection
	*  @param index The zero-based index of the element to retrieve
	*/
	RecognizedSpeechAlternate* operator[](int index) ;

	/**
	* Adds an item to the Collection
	*  @param item The object to add to the
	*/
	void add(RecognizedSpeechAlternate *item);

	/**
	* Adds an item to the Collection
	*  @param confidence The measure of certainty for a RecognizedSpeechAlternate
	*  @param text The normalized text obtained by a recognition engine
	*/
	void add(std::string text, float confidence);

	/**
	* Removes all items from the Collection
	*/
	void clear() ;

	/**
	* Determines whether the Collection contains a specific value.
	* @param item The object to locate in the Collection.
	*/
	bool contains(RecognizedSpeechAlternate *item) ;

	/**
	* Removes the first occurrence of a specific object from the Collection.
	* @param item The object to remove from the Collection
	*/
	bool remove(RecognizedSpeechAlternate *item) ;

	/**
	* Sorts the internal array by confidence
	*/
	void sort() ;
};

}/* Sensors */ } /* HAL */ } /* Robotics */

#endif // __RECOGNIZED_SPEECH_H__

