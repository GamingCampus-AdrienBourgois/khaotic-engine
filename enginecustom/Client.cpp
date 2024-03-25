#include "Client.h"

Client::Client() : m_socket(INVALID_SOCKET) {}

Client::~Client() {
    Disconnect();
}

bool Client::Connect(const char* serverAddress, int serverPort) {
    // Initialise les sockets Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        // Gestion de l'erreur
        return false;
    }

    // Crée un socket pour le client
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        // Gestion de l'erreur
        WSACleanup();
        return false;
    }

    // Configure l'adresse et le port du serveur auquel se connecter
    //sockaddr_in serverAddr;
    //serverAddr.sin_family = AF_INET;
    //serverAddr.sin_addr.s_addr = inet_addr(serverAddress); // Adresse IP du serveur
    //serverAddr.sin_port = htons(serverPort); // Port du serveur

    // Se connecte au serveur
    //if (connect(m_socket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        // Gestion de l'erreur
        closesocket(m_socket);
        WSACleanup();
        return false;
    }

   // return true;
//}

void Client::Disconnect() {
    // Déconnecte le client du serveur en fermant le socket
    if (m_socket != INVALID_SOCKET) {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
    WSACleanup();
}

bool Client::Send(const char* message) {
    // Envoie un message au serveur
    int result = send(m_socket, message, strlen(message), 0);
    if (result == SOCKET_ERROR) {
        // Gestion de l'erreur
        return false;
    }
    return true;
}
