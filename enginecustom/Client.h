#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h> // Pour les fonctionnalités de communication réseau sous Windows

// Déclaration de la classe Client
class Client {
public:
    Client(); // Constructeur
    ~Client(); // Destructeur

    bool Connect(const char* serverAddress, int serverPort); // Se connecte au serveur
    void Disconnect(); // Déconnecte le client du serveur

    bool Send(const char* message); // Envoie un message au serveur

private:
    SOCKET m_socket; // Socket du client
};

#endif // CLIENT_H

