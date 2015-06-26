#ifndef __DETECTED_HUMAN_FACES_H__
#define __DETECTED_HUMAN_FACES_H__

#include <uRobotics/hal/sensors/HumanFace.h>
#include <uRobotics/api/SharedVariableGeneric.h>

using namespace Robotics::HAL::Sensors;

class DetectedHumanFaces : public SharedVariableGeneric< std::vector<HumanFace*> >
{
private:
	DetectedHumanFaces(void);
	DetectedHumanFaces(const DetectedHumanFaces&);
public:
	DetectedHumanFaces(const std::string& name);
	DetectedHumanFaces(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const RecognizedSpeech& value, std::string& serializedData) const;
	virtual bool serialize(const HumanFace& value, std::stringstream& ss) const;
	virtual bool deserialize(const std::string& serializedData, RecognizedSpeech& value) const;
};


#endif // __RECOGNIZED_SPEECH_SHARED_VARIABLE_H__

#include <uRobotics/utilities/Scanner.h>

DetectedHumanFaces::DetectedHumanFaces(const std::string& name):
SharedVariableGeneric<std::vector<HumanFace*>>(name){}

DetectedHumanFaces::DetectedHumanFaces(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize):
SharedVariableGeneric<std::vector<HumanFace*>>(commandManager, variableName, initialize){}

const std::string DetectedHumanFaces::getTypeName() const{
	return std::string("HumanFace");
}

const bool DetectedHumanFaces::isArray() const{
	return true;
}

const int DetectedHumanFaces::getLength() const{
	return -1;
}

bool DetectedHumanFaces::serialize(const std::vector<HumanFace>& value, std::string& serializedData) const{

	std::stringstream ss;
	if(value.count() < 1){
		serializedData = std::string("null");
		return true;
	}

	sb = new StringBuilder();
	serialize(value[0], ss);
	for (size_t i = 1; i < value.size(); ++i)
	{
		ss << ' ';
		serialize(value[i], ss);	
	}
	serializedData = ss.str();
	return true;
}

bool DetectedHumanFaces::serialize(const HumanFace& value, std::stringstream& ss) const{
	// 1. Write open brace '{'
	// 2. Write white space
	ss << "{ ";
	
	// 3. Write quoted name followed by one space
	ss << "\\\"";
	ss << value.getName();
	ss << "\\\" ";

	// 4. Write Pan
	ss << value.getPan();

	// 5. Write space
	ss << ' ';

	// 6. Write Tilt
	ss << value.getTilt();

	// 7. Write space
	ss << ' ';

	// 8. Write confidence
	ss << value.getConfidence();

	// 9. Write white space followed by closing brace '}'
	ss << " }";

	return true;
}

bool DetectedHumanFaces::deserialize(const std::string& serializedData, std::vector<HumanFace>& value) const{
	value.clear();
	if (serializedData.empty() || (serializedData.compare("null") == 0))
	{
		value = null;
		return true;
	}
	
	size_t cc = 0;
	HumanFace currentFace;
	while ((serializedData.size() - cc) >= 15) {
		if(!deserialize(serializedData, cc, currentFace)){
			value.clear();
			return false;
		}
		faces.push_back(currentFace);
		while ((cc < serializedData.size()) && (serializedData[cc] != '{'))
			++cc;
	}
	return true;
}

bool DetectedHumanFaces::deserialize(const std::string& serializedData, size_t& cc, HumanFace& value) const{
	size_t start;
	size_t end;
	std::string name;
	double pan;
	double tilt;
	double confidence;

	if (serializedData.empty() || (serializedData.substr(cc, 4).compare("null") == 0)) {
		cc += 4;
		return false;
	}

	if (serializedData.size() < 15)
		return false;
	// 1. Read open brace '{'
	if (serializedData[cc++] != '{')
		return false;
	// 2. Read white space
	if (serializedData[cc++] != ' ')
		return false;

	// 3. Read name
	// 3.1. Read escaped double quotes
	if (!Scanner::readChar('\\', serializedData, cc) || !Scanner::readChar('"', serializedData, cc))
		return false;
	// 3.2. Read Name
	start = cc;
	while (cc < serializedData.size()) {
		// 3.3. Read escaped double quotes
		if (Scanner::readChar('\\', serializedData, cc) && Scanner::readChar('"', serializedData, cc))
			break;
	}

	// 3.4. Extract person name
	end = cc - 2;
	if ((end - start) < 1)
		return false;
	name = serializedData.substr(start, end - start);
	
	// 4. Read white space
	if (!Scanner::readChar(' ', serializedData, cc))
		return false;

	// 5. Read Pan
	if (!Scanner::xtractDouble(serializedData, cc, pan) ||
		(pan < HumanFace.MinimumPan) || (pan > HumanFace.MaximumPan))
		return false;

	// 6. Read white space
	if (!Scanner::readChar(' ', serializedData, cc))
		return false;

	// 7. Read Tilt
	if (!Scanner::xtractDouble(serializedData, cc, tilt) ||
		(tilt < HumanFace.MinimumTilt) || (tilt > HumanFace.MaximumTilt))
		return false;

	// 8. Read white space
	if (!Scanner::readChar(' ', serializedData, cc))
		return false;

	// 9. Read confidence
	if (!Scanner::xtractDouble(serializedData, cc, confidence) ||
		(confidence < 0) || (confidence > 1))
		return false;

	// A. Read white space
	if (!Scanner::readChar(' ', serializedData, cc))
		return false;

	// B. Read closing brace '}'
	if (!Scanner::readChar('}', serializedData, cc))
		return false;

	try {
		value = HumanFace(name, pan, tilt, confidence);
	}
	catch { return false; }
	return true;
}
