/* 
 * File:   Response.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#pragma once
#ifndef __RESPONSE_H__
#define	__RESPONSE_H__

#include <string>
#include <sstream>
#include <iostream>
#include <boost/regex.hpp>
#include "MessageBase.h"
#include "Command.h"

class Response :
	public MessageBase
{
private:
	// static boost::regex responseParser;

public:
	bool success;

public:
	Response(const Response& response);
	Response(const std::string& commandName);
	Response(const std::string& commandName, const bool& success);
	Response(const std::string& commandName, const std::string& parameters, const bool& success, const int& id);

	virtual ~Response(void);
	virtual std::string getStringToSend() const;
	static Response* parse(const std::string& s);
	static Response* createFromCommand(const Command& command, const bool& success);
	friend std::ostream& operator<<(std::ostream& os, const Response& response);
	friend std::ostream& operator<<(std::ostream& os, const Response*& response);
};

#endif // __RESPONSE_H__