#include "systemclass.h"
#include "server.h" // Assurez-vous que le chemin d'accès est correct pour inclure le fichier server.h
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    SystemClass* System;
    bool result;

    // Create the system object.
    System = new SystemClass;

    // Initialize and run the system object.
    result = System->Initialize();
    if (result)
    {
        // Start the TCP server
        Network::TCP::Server server;
        if (!server.start(12345)) // Start the server on port 12345
        {
            // Handle server start failure
            std::cerr << "Failed to start the TCP server." << std::endl;
            return -1;
        }

        // Run the system
        System->Run();

        // Stop the TCP server when the system finishes running
        server.stop();
    }

    // Shutdown and release the system object.
    System->Shutdown();
    delete System;
    System = nullptr;

    return 0;
}
