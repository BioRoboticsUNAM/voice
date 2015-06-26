#pragma once
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <algorithm> // std::min / std::max
#include "uRobotics/utilities/Scanner.h"

class Parser
{
	private: 
		Parser(void);
		virtual ~Parser(void);
	
	public:

		/**
		* Decodes the data contained in a received response. A return value indicates whether the operation succeeded
		* @param s	std::string which contains the data to parse
		* @param variableType	When this method returns contains the type of the variable coded in the input std::string if the conversion succeeded, or null if the conversion failed.
		* @param isArray	When this method returns is set to true if the conversion succeded and the variable coded in the input std::string is an array, false otherwise.
		* @param arrayLength	When this method returns contains the size of the array if the conversion succeded and the variable coded in the input std::string is an array, -1 otherwise.
		* @param variableName	When this method returns contains the name of the variable coded in the input std::string if the conversion succeeded, or null if the conversion failed.
		* @param variableData	When this method returns contains the content of the variable coded in the input std::string if the conversion succeeded, or the null if the conversion failed.
		* @return true if the the data extraction succeeded, false otherwise
		*/
		static bool parseSharedVariable(const std::string& s, std::string& variableType,
			bool& isArray, int& arrayLength, std::string& variableName, std::string& variableData);
		
		/**
		* Extracts the type, name and data from a shared variable
		* @param s	String from which the variable will be extracted
		* @param cc	The search starting position
		* @param varType	When this method returns contains the type of the variable found in s if the extraction succeded, or null if the extraction failed.
		* @param varName	When this method returns contains the name of the variable found in s if the extraction succeded, or null if the extraction failed.
		* @param isArray	When this method returns is set to true if a variable was found in s and it is an array, or false otherwise
		* @param arraySize	When this method returns contains the length of the array of the variable found in s if the extraction succeded and the variable is an array, or -1 otherwise
		* @return true if the extraction succeded, false otherwise
		*/
		//[Obsolete]
		static bool xtractSharedVariableData(const std::string& s, size_t& cc, std::string& varType,
			std::string& varName, bool& isArray, int& arraySize);

		/**
		* Extracts the type, name and data from a shared variable
		* @param s	String from which the variable will be extracted
		* @param cc	The search starting position
		* @param varType	When this method returns contains the type of the variable found in s if the extraction succeded, or null if the extraction failed.
		* @param varName	When this method returns contains the name of the variable found in s if the extraction succeded, or null if the extraction failed.
		* @param isArray	When this method returns is set to true if a variable was found in s and it is an array, or false otherwise
		* @param arraySize	When this method returns contains the length of the array of the variable found in s if the extraction succeded and the variable is an array, or -1 otherwise
		* @param data	When this method returns contains the data of the variable found in s if the extraction succeded, or null if the extraction failed.
		* @return true if the extraction succeded, false otherwise
		*/
		//[Obsolete]
		static bool xtractSharedVariableData(const std::string& s, size_t& cc,
			std::string& varType, std::string& varName, bool& isArray, int& arraySize, std::string& data);

		/**
		* Extracts the first module name found inside a std::string
		* @param s	String from which the module name will be extracted
		* @param cc	The search starting position
		* @param moduleName	When this method returns contains the first module name found in s if the extraction succeded, or null if the extraction failed.
		* @return True if the extraction succeded and a valid module name was found in s starting at cc, false otherwise
		*/
		static bool xtractModuleName(const std::string& s, size_t& cc, std::string& moduleName);

		/**
		* Extracts the first command name found inside a std::string
		* @param s	String from which the command name will be extracted
		* @param cc	The search starting position
		* @param commandName	When this method returns contains the first command name found in s if the extraction succeded, or null if the extraction failed.
		* @return True if the extraction succeded and a valid command name was found in s starting at cc, false otherwise
		*/
		static bool xtractCommandName(const std::string& s, size_t& cc, std::string& commandName);

		/**
		* Advances the read header until no spaces are found
		* @param s	Input std::string
		* @param cc	Read header
		*/
		static void skipSpaces(const std::string& s, size_t& cc);

		/**
		* Extracts the first command parameters found inside a std::string
		* @param s	String from which the command parameters will be extracted
		* @param cc	The search starting position
		* @param parameters	When this method returns contains the first command parameters found in s if the extraction succeded, or null if the extraction failed.
		* @return True if the extraction succeded and a valid command parameters was found in s starting at cc, false otherwise
		*/
		static bool xtractCommandParams(const std::string& s, size_t& cc, std::string& parameters);

		/**
		* Extracts the first @id found inside a std::string
		* @param s	String from which the @id will be extracted
		* @param cc	The search starting position
		* @param id	When this method returns contains the id found in s if the extraction succeded, or -1 if the extraction failed.
		* @return True if the extraction succeded and a valid id was found in s starting at cc, false otherwise
		*/
		static bool xtractId(const std::string& s, size_t& cc, int& id);

		/**
		* Extracts the first C-type identifier found inside a std::string
		* @param s	String from which the identifier will be extracted
		* @param cc	The search starting position
		* @param identifier	When this method returns contains the first C-type identifier found in s if the extraction succeded, or null if the extraction failed.
		* @return True if the extraction succeded and a valid C-type identifier was found in s starting at cc, false otherwise
		*/
		static bool xtractIdentifier(const std::string& s, size_t& cc, std::string& identifier);

		/**
		* Extracts the first result (1 or 0) found inside a std::string
		* @param s	String from which the result will be extracted
		* @param cc	The search starting position
		* @param result	When this method returns contains the result found in s if the extraction succeded, or -1 if the extraction failed.
		* @return True if the extraction succeded and a valid result was found in s starting at cc, false otherwise
		*/
		static bool xtractResult(const std::string& s, size_t& cc, int& result);
};

#endif // __PARSER_H__