#ifndef NETWORK_H
#define NETWORK_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

const int DEFAULT_PORT = 12345; // Définissons le port par défaut

class Network {
public:
    Network();
    ~Network();
    bool Initialize();
    bool CreateSocket();
    bool BindSocket(int port);
    bool Listen();
    SOCKET Accept();

    bool Send(SOCKET clientSocket, const char* message);
    int Receive(SOCKET clientSocket, char* buffer, int bufferSize);

private:
    WSADATA wsaData;
    SOCKET serverSocket;
};

#endif // NETWORK_H
