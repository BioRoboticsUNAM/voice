#ifndef __HUMAN_FACE_H__
#define __HUMAN_FACE_H__

#include <string>
#include <vector>
#include <boost/regex.hpp>

namespace Robotics{ namespace HAL{ namespace Sensors{

/**
* Represents a human Face
*/
class HumanFace {
public:

	/**
	* The maximum horizontal deviation angle of the centroid of the detected human face from the centre of the image in radians
	*/
	static const double MaximumPan;

	/**
	* The maximum vertical deviation angle of the centroid of the detected human face from the center of the image in radians
	*/
	static const double MaximumTilt;

	/**
	* The maximum horizontal deviation angle of the centroid of the detected human face from the center of the image in radians
	*/
	static const double MinimumPan;

	/**
	* The minimum vertical deviation angle of the centroid of the detected human face from the center of the image in radians
	*/
	static const double MinimumTilt;

private:
	/**
	* The associated name to the detected human face
	*/
	std::string name;

	/**
	* The horizontal deviation angle of the centroid of the detected human face from the center of the image
	*/
	double pan;

	/**
	* The vertical deviation angle of the centroid of the detected human face from the center of the image
	*/
	double tilt;

	/**
	* Value between 0 and 1 that represents the confidence of the detected human face respect to its pattern
	*/
	double confidence;

public:
	/**
	* Regular expression used to validate names
	*/
	static const boost::regex RxNameValidator;

	/**
	* Initializes a new instance of HumanFace
	*/
	HumanFace();

	/**
	* Initializes a new instance of HumanFace
	* @param name The associated name to the detected human face
	* @param pan The horizontal deviation angle of the centroid of the detected human face from the center of the image
	* @param tilt The vertical deviation angle of the centroid of the detected human face from the center of the image
	* @param confidence Value between 0 and 1 that represents the confidence of the detected human face respect to its pattern
	*/
	HumanFace(const std::string& name, const double& pan, const double& tilt, const double& confidence);

	/**
	* Gets or sets the associated name to the detected human face
	*/
	std::string getName() const ;

	/**
	* Gets or sets the associated name to the detected human face
	*/
	void setName(const std::string& value);

	/**
	* Gets or sets the horizontal deviation angle of the centroid of the detected human face from the center of the image
	*/
	double getPan() const ;

	/**
	* Gets or sets the horizontal deviation angle of the centroid of the detected human face from the center of the image
	*/
	void setPan(const double& value);

	/**
	* Gets or sets the vertical deviation angle of the centroid of the detected human face from the center of the image
	*/
	double getTilt() const ;

	/**
	* Gets or sets the vertical deviation angle of the centroid of the detected human face from the center of the image
	*/
	void setTilt(const double& value);

	/**
	* Gets or sets a value between 0 and 1 that represents the confidence of the detected human face respect to its pattern
	*/
	double getConfidence() const ;

	/**
	* Gets or sets a value between 0 and 1 that represents the confidence of the detected human face respect to its pattern
	*/
	void setConfidence(const double& value);
};


}/* Sensors */ } /* HAL */ } /* Robotics */

#endif // __HUMAN_FACE_H__