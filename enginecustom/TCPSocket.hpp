#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP
#pragma once

#include "Sockets.hpp"

#include <stdlib.h>
#include <string>

class TCPSocket
{
public:
	TCPSocket();
	~TCPSocket();

	bool Connect(const std::string& ipaddress, unsigned short port);
	int Send(const char* data, unsigned int len);
	int Receive(char* buffer, unsigned int len);
	bool Send(const unsigned char* data, unsigned short len);
	bool Receive(std::vector<unsigned char>& buffer);

private:
	SOCKET mSocket;
};

#endif // TCPSOCKET_HPP