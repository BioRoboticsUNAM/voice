/* 
 * File:   session.h
 * Author: haime
 * Modified by: Mauricio Matamoros
 *
 * Created on 8 de enero de 2013, 10:55 AM
 */

#ifndef SESSION_H
#define	SESSION_H

#include <cstdlib>
#include <iostream>
#include <queue>
#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/pending/queue.hpp>
#include <boost/asio.hpp>
#include "uRobotics/sockets/TcpPacket.h"
#include "uRobotics/utilities/ProducerConsumer.h"

using boost::asio::ip::tcp;

namespace Robotics { namespace Sockets {

class Session {
public:
	Session(boost::asio::io_service& io_service, Robotics::Utilities::ProducerConsumer<TcpPacket*>& q);
	virtual ~Session();
	void handle_write(const boost::system::error_code& error);
	tcp::socket& socket();
	void start();
	void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
    void print(char *data ,int max_length);
private:
	tcp::socket sckt;
	static const int MAX_LENGTH = 4194304;
	char data[MAX_LENGTH];
	Robotics::Utilities::ProducerConsumer<TcpPacket*>& packetsReceived;
};

} /* Sockets */ } /* Robotics */

#endif	/* SESSION_H */

