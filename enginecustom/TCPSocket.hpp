#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP
#pragma once

#include "Sockets.hpp"

#include <string>

class TCPSocket
{
public:
	TCPSocket();
	~TCPSocket();

	bool Connect(const std::string& ipaddress, unsigned short port);

private:
	SOCKET mSocket;
};

#endif // TCPSOCKET_HPP