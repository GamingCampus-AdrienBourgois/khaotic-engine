#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <winsock2.h> // Pour les fonctionnalités de communication réseau sous Windows

// Déclaration de la classe NetworkManager
class NetworkManager {
public:
    NetworkManager(); // Constructeur
    ~NetworkManager(); // Destructeur

    bool Initialize(); // Initialise le gestionnaire de réseau
    void Shutdown(); // Arrête le gestionnaire de réseau

    // Ajoute ici d'autres fonctions nécessaires pour la communication réseau
    // (par exemple, fonctions pour envoyer/recevoir des messages, gérer les connexions, etc.)
};

#endif // NETWORKMANAGER_H

