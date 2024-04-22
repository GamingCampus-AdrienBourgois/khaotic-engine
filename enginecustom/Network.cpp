#include "Network.h"

Network::Network() : serverSocket(INVALID_SOCKET), clientSocket(INVALID_SOCKET) {}

Network::~Network() {
    closesocket(serverSocket);
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
    clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de l'acceptation de la connexion entrante" << std::endl;
        closesocket(serverSocket);
        return INVALID_SOCKET;
    }
    return clientSocket;
}

bool Network::Connect(const std::string& ipAddress) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(DEFAULT_PORT);
    inet_pton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la connexion au serveur" << std::endl;
        closesocket(clientSocket);
        return false;
    }
    return true;
}

bool Network::Send(SOCKET socket, const std::string& message) {
    int bytesSent = send(socket, message.c_str(), message.length(), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Erreur lors de l'envoi des données" << std::endl;
        return false;
    }
    return true;
}

std::string Network::Receive(SOCKET socket) {
    char buffer[4096];
    int bytesReceived = recv(socket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        return std::string(buffer);
    }
    else {
        std::cerr << "Erreur lors de la réception des données" << std::endl;
        return ""; // Ou une indication d'erreur
    }
}
