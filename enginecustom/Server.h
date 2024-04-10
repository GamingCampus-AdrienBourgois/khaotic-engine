<<<<<<< Updated upstream
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
=======
#pragma once

#include <memory>

namespace Network
{
	namespace Messages {
		class Base;
	}
	namespace TCP
	{
		class ServerImpl;
		class Server
		{
		public:
			Server();
			Server(const Server&) = delete;
			Server& operator=(const Server&) = delete;
			Server(Server&&);
			Server& operator=(Server&&);
			~Server();

			bool start(unsigned short _port);
			void stop();
			void update();
			bool sendTo(uint64_t clientid, const unsigned char* data, unsigned int len);
			bool sendToAll(const unsigned char* data, unsigned int len);
			std::unique_ptr<Messages::Base> poll();

		private:
			std::unique_ptr<ServerImpl> mImpl;
		};
	}
}
>>>>>>> Stashed changes
