#ifndef NETWORK_H
#define NETWORK_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

const int DEFAULT_PORT = 12345;

class Network {
public:
    Network();
    ~Network();
    bool Initialize();
    bool CreateSocket();
    bool BindSocket(int port);
    bool Listen();
    SOCKET Accept();
    bool Connect(const std::string& ipAddress);
    bool Send(SOCKET socket, const std::string& message);
    std::string Receive(SOCKET socket);

    // Déplacer la déclaration de clientSocket ici pour le rendre accessible depuis Main.cpp
    SOCKET clientSocket;

private:
    WSADATA wsaData;
    SOCKET serverSocket;
};

#endif // NETWORK_H
