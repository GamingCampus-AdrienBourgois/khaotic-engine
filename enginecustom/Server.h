#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h> // Pour les fonctionnalit�s de communication r�seau sous Windows

// D�claration de la classe Server
class Server {
public:
    Server(); // Constructeur
    ~Server(); // Destructeur

    bool Initialize(); // Initialise le serveur
    void Shutdown(); // Arr�te le serveur

    void Run(); // Boucle principale du serveur

private:
    // D�clare ici les membres priv�s n�cessaires pour le serveur de chat
    SOCKET m_listenSocket; // Socket d'�coute pour les nouvelles connexions
    bool m_running; // Indique si le serveur est en cours d'ex�cution
};

#endif // SERVER_H
