/* 
 * File:   TcpPacket.h
 * Author: haime
 * Modified by: Mauricio Matamoros
 *
 * Created on 8 de enero de 2013, 01:08 PM
 */

#ifndef TCPPACKET_H
#define	TCPPACKET_H

#include <cstdlib>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "boost/thread/mutex.hpp"
#include "boost/thread/thread.hpp"
#include "boost/algorithm/string.hpp"

namespace Robotics{ namespace Sockets {

class TcpPacket {
public:
    TcpPacket(const char* data, size_t length);    
    ~TcpPacket();
	
	
	/**
	 * Gets a copy of the data received
     * @return a vector of chars containing the data received
     */
	std::vector<char> getData();
	/**
	 * Gets a copy of the data received
     * @param A pointer to a buffer where copy the data to
     * @param When this method returns contains the size of the buffer
     */
	void getData(char **buffer, size_t *bufferLength);
	/**
	 * Gets the length of the data received
     * @return the length of the data received
     */
	size_t getDataLenght();
	/**
	 * 
     * @param index
     * @return 
     */
	std::string getDataString(int index);
	/**
	 * 
     * @return 
     */
	std::vector<std::string>& getDataStrings();
	
private:
	char *data;
	size_t dataLength;
	std::vector<std::string> dataStrings;

};

} /* Sockets */ } /* Robotics */

#endif	/* TCPPACKET_H */
