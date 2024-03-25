#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h> // Pour les fonctionnalit�s de communication r�seau sous Windows

// D�claration de la classe Client
class Client {
public:
    Client(); // Constructeur
    ~Client(); // Destructeur

    bool Connect(const char* serverAddress, int serverPort); // Se connecte au serveur
    void Disconnect(); // D�connecte le client du serveur

    bool Send(const char* message); // Envoie un message au serveur

private:
    SOCKET m_socket; // Socket du client
};

#endif // CLIENT_H

