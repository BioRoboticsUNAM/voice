/* 
 * File:   SimpleConnectionManager.h
 * Author: Mauricio Matamoros
 *
 * Created on Aug 12, 2013 de 2013, 10:53 AM
 */

#pragma once
#ifndef __SIMPLE_CONNECTION_MANAGER_H__
#define	__SIMPLE_CONNECTION_MANAGER_H__

#include <cstdlib>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include "uRobotics/utilities/ProducerConsumer.h"
#include "uRobotics/sockets/Session.h"

using boost::asio::ip::tcp;
using namespace Robotics::Sockets;
using namespace Robotics::Utilities;
typedef boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> scoped_lock;

class SimpleConnectionManager {
private:
	unsigned short port;
	bool running;
	boost::asio::io_service *service;
	tcp::acceptor *acceptor;
	ProducerConsumer<TcpPacket*> packetsReceived;
	std::vector<tcp::socket*> sockets;
	boost::thread* mainThread;
	/**
	* Number of connected clients
	*/ 
	boost::interprocess::interprocess_semaphore nccSemaphore;
	/**
	* Mutex used to acces the connected sockets list
	*/
	boost::interprocess::interprocess_mutex socketsMutex;	


public:
	SimpleConnectionManager();
	SimpleConnectionManager(unsigned short port);
	virtual ~SimpleConnectionManager();
	unsigned short getPort();
	void setPort(unsigned short port);
	bool isRunning();
	void handleAccept(Session *new_session, const boost::system::error_code& error);
	ProducerConsumer<TcpPacket*>& getPacketsReceived();
	bool sendTo(tcp::socket& socket, const std::string& s) const;
	size_t sendToAll(const std::string& s);
	void start();
	void stop();
	void waitClientConnected();
	bool waitClientConnected(const int& timeout);

private:
	void mainThreadTask();
	void beginAcceptConnection();
	void emptyPacketsReceivedQ();
	
	
};

#endif	/* __SIMPLE_CONNECTION_MANAGER_H__ */