#include "systemclass.h"
#include "Network.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    // Créer l'objet système.
    SystemClass* System;
    bool result;

    // Create the system object.
    System = new SystemClass;

    // Initialize and run the system object.
    result = System->Initialize();
    if (result)
    {
        Logger::Get().Log("System initialized", __FILE__, __LINE__);

        // Initialiser le réseau
        Network network;

        // Initialisation de Winsock
        if (!network.Initialize()) {
            return 1;
        }

        // Création du socket
        if (!network.CreateSocket()) {
            return 1;
        }

        // Bind du socket
        if (!network.BindSocket(DEFAULT_PORT)) {
            return 1;
        }

        // Mise en écoute
        if (!network.Listen()) {
            return 1;
        }

        std::cout << "Serveur en attente de connexion sur le port " << DEFAULT_PORT << std::endl;

        // Accepter les connexions entrantes
        SOCKET clientSocket = network.Accept();
        if (clientSocket == INVALID_SOCKET) {
            return 1;
        }

        // Exemple d'envoi de message
        const char* messageToSend = "Bonjour, monde!";
        network.Send(clientSocket, messageToSend);

        // Fermeture du socket client
        closesocket(clientSocket);

        System->Run();
    }

    // Shutdown and release the system object.
    System->Shutdown();
    delete System;
    System = 0;

    return 0;
}
