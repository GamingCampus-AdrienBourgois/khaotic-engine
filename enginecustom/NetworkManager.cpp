#include "NetworkManager.h"

NetworkManager::NetworkManager() {}

NetworkManager::~NetworkManager() {
    Shutdown();
}

bool NetworkManager::Initialize() {
    // Initialise les sockets Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        // Gestion de l'erreur
        return false;
    }
    return true;
}

void NetworkManager::Shutdown() {
    // Arrête le gestionnaire de réseau en libérant les ressources Winsock
    WSACleanup();
}
