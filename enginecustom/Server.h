#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h> // Pour les fonctionnalités de communication réseau sous Windows

// Déclaration de la classe Server
class Server {
public:
    Server(); // Constructeur
    ~Server(); // Destructeur

    bool Initialize(); // Initialise le serveur
    void Shutdown(); // Arrête le serveur

    void Run(); // Boucle principale du serveur

private:
    // Déclare ici les membres privés nécessaires pour le serveur de chat
    SOCKET m_listenSocket; // Socket d'écoute pour les nouvelles connexions
    bool m_running; // Indique si le serveur est en cours d'exécution
};

#endif // SERVER_H
