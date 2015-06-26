/* 
 * File:   ISharedVariableInfo.h
 * Author: Mauricio Matamoros
 *
 */

#pragma once
#ifndef __I_SHARED_VARIABLE_INFO_H__
#define __I_SHARED_VARIABLE_INFO_H__

#include <string>

class ISharedVariableInfo{
	public:
		// Empty virtual destructor for proper cleanup
		virtual ~ISharedVariableInfo(){}

		/**
		Gets a value indicating if the variable is an array
		*/
		const virtual bool isArray() const = 0;

		/**
		If the variable is an array gets the length of the array, else returns -1
		*/
		const virtual int getLength() const = 0;

		/**
		Gets the name of the SharedVariable
		*/
		const virtual std::string getName() const = 0;

		/**
		Gets the global name of the type of the SharedVariable
		*/
		const virtual std::string getTypeName() const = 0;
};

#endif // __I_SHARED_VARIABLE_INFO_H__

