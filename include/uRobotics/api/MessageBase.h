/* 
 * File:   MessageBase.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#pragma once
#ifndef __MESSAGE_BASE_H__
#define	__MESSAGE_BASE_H__

#include <string>
#include <sstream>

class MessageBase
{
//private:

public:
	std::string commandName;
	std::string parameters;
	int id;

public:
	MessageBase(const std::string& commandName);
	MessageBase(const std::string& commandName, const std::string& parameters, const int& id);
	virtual ~MessageBase(void);
	virtual std::string getEscapedParameters() const;
	virtual void setEscapedParameters(const std::string& p);
	virtual std::string getStringToSend() const = 0;
	virtual bool hasParams() const;
};

#endif // __MESSAGE_BASE_H__