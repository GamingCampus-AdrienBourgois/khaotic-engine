#include "SystemClass.h"
#include "Network.h"

bool ChooseRole() {
    int result = MessageBoxA(nullptr, "Voulez-vous d�marrer en tant que serveur ?", "Choix du r�le", MB_YESNO | MB_ICONQUESTION);
    return (result == IDYES);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Cr�er l'objet syst�me.
    SystemClass* System;
    bool result;

    // Create the system object.
    System = new SystemClass;

    // Initialize and run the system object.
    result = System->Initialize();
    if (result) {
        Logger::Get().Log("System initialized", __FILE__, __LINE__);

        // Choix du r�le (serveur ou client)
        bool isServer = ChooseRole();

        if (isServer) {
            // Code pour le serveur
            Network network;

            // Initialisation du r�seau
            if (!network.Initialize()) {
                Logger::Get().Log("Erreur lors de l'initialisation du r�seau", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            // Cr�ation du socket serveur
            if (!network.CreateSocket()) {
                Logger::Get().Log("Erreur lors de la cr�ation du socket serveur", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            // Liaison du socket � un port
            if (!network.BindSocket(DEFAULT_PORT)) {
                Logger::Get().Log("Erreur lors de la liaison du socket serveur au port", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            // Mise en �coute de nouvelles connexions entrantes
            if (!network.Listen()) {
                Logger::Get().Log("Erreur lors de la mise en �coute du socket serveur", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            Logger::Get().Log("Serveur en �coute sur le port " + std::to_string(DEFAULT_PORT), __FILE__, __LINE__);

            // Acceptation d'une nouvelle connexion
            SOCKET clientSocket = network.Accept();
            if (clientSocket == INVALID_SOCKET) {
                Logger::Get().Log("Erreur lors de l'acceptation de la connexion entrante", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            // Gestion des messages entrants
            while (true) {
                std::string message = network.Receive(clientSocket);
                if (message.empty()) {
                    Logger::Get().Log("Erreur lors de la r�ception du message", __FILE__, __LINE__);
                    break; // Sort de la boucle en cas d'erreur
                }
                Logger::Get().Log("Message re�u du client : " + message, __FILE__, __LINE__);
            }

            // Fermeture du socket client
            closesocket(clientSocket);
        }
        else {
            // Code pour le client
            Network network;

            // Initialisation du r�seau
            if (!network.Initialize()) {
                Logger::Get().Log("Erreur lors de l'initialisation du r�seau", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            // Cr�ation du socket client
            if (!network.CreateSocket()) {
                Logger::Get().Log("Erreur lors de la cr�ation du socket client", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            // Connexion au serveur
            std::string serverIpAddress = "127.0.0.1"; // Adresse IP du serveur
            if (!network.Connect(serverIpAddress)) {
                Logger::Get().Log("Erreur lors de la connexion au serveur", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            // Envoi d'un message au serveur
            std::string message = "Bonjour, je suis le client !";
            if (!network.Send(network.clientSocket, message)) {
                Logger::Get().Log("Erreur lors de l'envoi du message", __FILE__, __LINE__);
                return 1; // Quitte le programme en cas d'erreur
            }

            Logger::Get().Log("Message envoy� au serveur : " + message, __FILE__, __LINE__);
        }

        System->Run();
    }

    // Shutdown and release the system object.
    System->Shutdown();
    delete System;
    System = 0;

    return 0;
}
