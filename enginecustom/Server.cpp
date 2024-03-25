#include "Server.h"

Server::Server() : m_listenSocket(INVALID_SOCKET), m_running(false) {}

Server::~Server() {
    Shutdown();
}

bool Server::Initialize() {
    // Initialise les sockets Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        // Gestion de l'erreur
        return false;
    }

    // Cr�e un socket pour �couter les nouvelles connexions
    m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_listenSocket == INVALID_SOCKET) {
        // Gestion de l'erreur
        WSACleanup();
        return false;
    }

    // Configure l'adresse et le port pour �couter les connexions entrantes
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // �coute sur toutes les interfaces r�seau
    serverAddr.sin_port = htons(12345); // Port d'�coute (modifiable selon tes besoins)

    // Associe l'adresse et le port au socket d'�coute
    if (bind(m_listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        // Gestion de l'erreur
        closesocket(m_listenSocket);
        WSACleanup();
        return false;
    }

    // Met le socket en mode �coute (attente de connexions entrantes)
    if (listen(m_listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        // Gestion de l'erreur
        closesocket(m_listenSocket);
        WSACleanup();
        return false;
    }

    // Indique que le serveur est pr�t � accepter les connexions
    m_running = true;

    return true;
}

void Server::Shutdown() {
    // Arr�te le serveur en fermant le socket d'�coute et en lib�rant les ressources Winsock
    if (m_listenSocket != INVALID_SOCKET) {
        closesocket(m_listenSocket);
        m_listenSocket = INVALID_SOCKET;
    }
    WSACleanup();
}

void Server::Run() {
    // Boucle principale du serveur
    while (m_running) {
        // G�re les connexions entrantes et les messages du chat
        // � impl�menter
    }
}