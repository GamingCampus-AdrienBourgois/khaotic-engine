<<<<<<< Updated upstream
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
