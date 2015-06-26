#ifndef __RECOGNIZED_SPEECH_SHARED_VARIABLE_H__
#define __RECOGNIZED_SPEECH_SHARED_VARIABLE_H__

#include <uRobotics/hal/sensors/RecognizedSpeech.h>
#include <uRobotics/api/SharedVariableGeneric.h>

using namespace Robotics::HAL::Sensors;

class RecognizedSpeechSharedVariable : public SharedVariableGeneric<RecognizedSpeech>
{
private:
	RecognizedSpeechSharedVariable(void);
	RecognizedSpeechSharedVariable(const RecognizedSpeechSharedVariable&);
public:
	RecognizedSpeechSharedVariable(const std::string& name);
	RecognizedSpeechSharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize);
	const std::string getTypeName() const;
	const bool isArray() const;
	const int getLength() const;
protected:
	virtual bool serialize(const RecognizedSpeech& value, std::string& serializedData) const;

	virtual bool deserialize(const std::string& serializedData, RecognizedSpeech& value) const;
};


#endif // __RECOGNIZED_SPEECH_SHARED_VARIABLE_H__

#include <uRobotics/utilities/Scanner.h>

RecognizedSpeechSharedVariable::RecognizedSpeechSharedVariable(const std::string& name):
SharedVariableGeneric<RecognizedSpeech>(name){}

RecognizedSpeechSharedVariable::RecognizedSpeechSharedVariable(SimpleCommandManager *commandManager, const std::string& variableName, const bool& initialize):
SharedVariableGeneric<RecognizedSpeech>(commandManager, variableName, initialize){}

const std::string RecognizedSpeechSharedVariable::getTypeName() const{
	return std::string("RecognizedSpeech");
}

const bool RecognizedSpeechSharedVariable::isArray() const{
	return true;
}

const int RecognizedSpeechSharedVariable::getLength() const{
	return -1;
}

bool RecognizedSpeechSharedVariable::serialize(const RecognizedSpeech& value, std::string& serializedData) const{

	std::stringstream ss;
	if(value.count() < 1){
		serializedData = std::string("null");
		return true;
	}

	// 1. Write open brace '{'
	// 2. Write white space
	ss << "{ ";

	// 3. Write the number of alternates
	ss << value.count();

	// 4. Write white space
	ss << ' ';

	// 5. Write all Alternates
	for (int i = 0; i < value.count(); ++i)
	{
		// 5.1. Write alternate text
		if(value[i].getText().find('"') != std::string::npos)
			return false;
		//sb.Append("\\\"");
		ss << '"';
		ss << value[i].getText();
		ss << '";'
		// 5.2. Write white space
		ss << ' ';
		// 5.3. Write confidence
		ss << value[i].getConfidence();
		// 5.4. Write white space
		ss << ' ';
	}

	// 1. Write close brace '}'
	ss << '}';
	serializedData = ss.str();

	return true;
}

bool RecognizedSpeechSharedVariable::deserialize(const std::string& serializedData, RecognizedSpeech& value) const{

	size_t count;
	RecognizedSpeech rs;
	size_t cc;
	size_t start;
	size_t end;
	std::string text;
	double confidence;

	value.clear();
	if (serializedData.empty() || (serializedData.compare("null") == 0))
		return true;

	if (serializedData.size() < 4)
		return false;
	cc = 0;
	// 1. Read open brace '{'
	if (serializedData[cc++] != '{')
		return false;
	// 2. Read white space
	if (serializedData[cc++] != ' ')
		return false;

	// 3. Read number of alternates
	if (!Scanner::xtractUInt16(serializedData, cc, count))
		return false;

	// 4. Read alternates
	for(int i = 0; i < count; ++i)
	{
		// 4.1. Read text
		// 4.1.1. Read double quotes
		Scanner::skipSpaces(serializedData, cc);
		if(!Scanner::readChar('"', serializedData, cc))
			return false;
		// 4.1.2. Read text
		start = cc;
		while (cc < serializedData.size())
		{
			// 4.1.3. Read double quotes
			if (Scanner::readChar('"', serializedData, cc))
				break;
			++cc;
		}
		end = cc - 1;
		// 4.1.4. Extract text
		if((end - start) < 1)
			return false;
		text = serializedData.substr(start, end - start);

		// 4.2. Read white space
		if (!Scanner::readChar(' ', serializedData, cc))
			return false;

		// 4.3 Read confidence
		if (!Scanner::xtractDouble(serializedData, cc, confidence))
			return false;

		// 4.4. Read white space
		if (!Scanner::readChar(' ', serializedData, cc))
			return false;

		rs.add(text, (float)confidence);
	}

	// 5. Read closing brace '}'
	if (!Scanner::readChar('}', serializedData, cc))
		return false;

	value = rs;
	return true;
}
