#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <winsock2.h> // Pour les fonctionnalit�s de communication r�seau sous Windows

// D�claration de la classe NetworkManager
class NetworkManager {
public:
    NetworkManager(); // Constructeur
    ~NetworkManager(); // Destructeur

    bool Initialize(); // Initialise le gestionnaire de r�seau
    void Shutdown(); // Arr�te le gestionnaire de r�seau

    // Ajoute ici d'autres fonctions n�cessaires pour la communication r�seau
    // (par exemple, fonctions pour envoyer/recevoir des messages, g�rer les connexions, etc.)
};

#endif // NETWORKMANAGER_H

