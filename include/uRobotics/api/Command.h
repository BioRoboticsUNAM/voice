/* 
 * File:   Command.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#pragma once
#ifndef __COMMAND_H__
#define	__COMMAND_H__

#include <string>
#include <sstream>
#include <iostream>
#include <boost/regex.hpp>
#include "MessageBase.h"

class Response;

class Command :
	public MessageBase
{
private:
	//static boost::regex commandParser;

public:
	Command(const Command& command);
	Command(const std::string& commandName);
	Command(const std::string& commandName, const std::string& parameters);
	Command(const std::string& commandName, const std::string& parameters, const int& id);

	virtual ~Command(void);
	virtual std::string getStringToSend() const;
	static Command* parse(const std::string& s);
	bool isMatch(const Response& response) const;
	friend std::ostream& operator<<(std::ostream& os, const Command& command);
	friend std::ostream& operator<<(std::ostream& os, const Command*& command);
};

#endif // __COMMAND_H__