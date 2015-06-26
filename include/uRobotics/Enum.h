/* 
 * File:   Enum.h
 * Author: Mauricio Matamoros
 *
 */

#pragma once
#ifndef __ENUM_H__
#define __ENUM_H__

#include <typeinfo>

namespace Robotics{

class Enum
{
public:
	virtual ~Enum(void){}
	operator int() const { return this->value; }
	bool operator== (const Enum& other) const{ return (typeid(*this) == typeid(other)) && (value == other.value); }
	bool operator!= (const Enum& other) const{ return (typeid(*this) != typeid(other)) || (value != other.value); }
protected:
	Enum(int v) : value(v){}
private:
	int value;
	Enum(void) : value(0){}
};

}

#endif // __ENUM_H__
