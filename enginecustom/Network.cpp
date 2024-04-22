#include "Network.h"

Network::Network() : serverSocket(INVALID_SOCKET) {}

Network::~Network() {
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
    WSACleanup();
}

bool Network::Initialize() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur lors de l'initialisation de Winsock" << std::endl;
        return false;
    }
    return true;
}

bool Network::CreateSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return false;
    }
    return true;
}

bool Network::BindSocket(int port) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors du binding du socket" << std::endl;
        closesocket(serverSocket);
        return false;
    }
    return true;
}

bool Network::Listen() {
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la mise en écoute du socket" << std::endl;
        closesocket(serverSocket);
        return false;
    }
    return true;
}

SOCKET Network::Accept() {
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de l'acceptation de la connexion entrante" << std::endl;
        closesocket(serverSocket);
        return INVALID_SOCKET;
    }
    return clientSocket;
}

bool Network::Send(SOCKET clientSocket, const char* message) {
    int bytesSent = send(clientSocket, message, strlen(message), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Erreur lors de l'envoi des données" << std::endl;
        return false;
    }
    return true;
}

int Network::Receive(SOCKET clientSocket, char* buffer, int bufferSize) {
    int bytesReceived = recv(clientSocket, buffer, bufferSize, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
    }
    else if (bytesReceived == 0) {
        std::cerr << "La connexion a été fermée par le client" << std::endl;
    }
    else {
        std::cerr << "Erreur lors de la réception des données" << std::endl;
    }
    return bytesReceived;
}
