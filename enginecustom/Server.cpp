#include "Server.h"

<<<<<<< Updated upstream
Server::Server() : m_listenSocket(INVALID_SOCKET), m_running(false) {}

Server::~Server() {
    Shutdown();
}

bool Server::Initialize() {
    // Initialise les sockets Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        // Gestion de l'erreur
        return false;
    }

    // Crée un socket pour écouter les nouvelles connexions
    m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_listenSocket == INVALID_SOCKET) {
        // Gestion de l'erreur
        WSACleanup();
        return false;
    }

    // Configure l'adresse et le port pour écouter les connexions entrantes
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Écoute sur toutes les interfaces réseau
    serverAddr.sin_port = htons(12345); // Port d'écoute (modifiable selon tes besoins)

    // Associe l'adresse et le port au socket d'écoute
    if (bind(m_listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        // Gestion de l'erreur
        closesocket(m_listenSocket);
        WSACleanup();
        return false;
    }

    // Met le socket en mode écoute (attente de connexions entrantes)
    if (listen(m_listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        // Gestion de l'erreur
        closesocket(m_listenSocket);
        WSACleanup();
        return false;
    }

    // Indique que le serveur est prêt à accepter les connexions
    m_running = true;

    return true;
}

void Server::Shutdown() {
    // Arrête le serveur en fermant le socket d'écoute et en libérant les ressources Winsock
    if (m_listenSocket != INVALID_SOCKET) {
        closesocket(m_listenSocket);
        m_listenSocket = INVALID_SOCKET;
    }
    WSACleanup();
}

void Server::Run() {
    // Boucle principale du serveur
    while (m_running) {
        // Gère les connexions entrantes et les messages du chat
        // À implémenter
    }
=======
#include "Sockets.h"
#include "Client.h"
#include "Messages.h"

#include <map>
#include <list>
#include <cassert>

namespace Network
{
	namespace TCP
	{
		class ServerImpl
		{
		public:
			ServerImpl() = default;
			~ServerImpl();

			bool start(unsigned short _port);
			void stop();
			void update();
			bool sendTo(uint64_t clientid, const unsigned char* data, unsigned int len);
			bool sendToAll(const unsigned char* data, unsigned int len);
			std::unique_ptr<Messages::Base> poll();

		private:
			std::map<uint64_t, Client> mClients;
			std::list<std::unique_ptr<Messages::Base>> mMessages;
			SOCKET mSocket{ INVALID_SOCKET };
		};
		ServerImpl::~ServerImpl()
		{
			stop();
		}

		bool ServerImpl::start(unsigned short _port)
		{
			assert(mSocket == INVALID_SOCKET);
			if (mSocket != INVALID_SOCKET)
				stop();
			mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (mSocket == INVALID_SOCKET)
				return false;

			if (!SetReuseAddr(mSocket) || !SetNonBlocking(mSocket))
			{
				stop();
				return false;
			}

			sockaddr_in addr;
			addr.sin_addr.s_addr = INADDR_ANY;
			addr.sin_port = htons(_port);
			addr.sin_family = AF_INET;
			if (bind(mSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0)
			{
				stop();
				return false;
			}
			if (listen(mSocket, SOMAXCONN) != 0)
			{
				stop();
				return false;
			}
			return true;
		}
		void ServerImpl::stop()
		{
			for (auto& client : mClients)
				client.second.disconnect();
			mClients.clear();
			if (mSocket != INVALID_SOCKET)
				CloseSocket(mSocket);
			mSocket = INVALID_SOCKET;
		}
		void ServerImpl::update()
		{
			if (mSocket == INVALID_SOCKET)
				return;

			//!< accept jusqu'à 10 nouveaux clients
			for (int accepted = 0; accepted < 10; ++accepted)
			{
				sockaddr_in addr = { 0 };
				socklen_t addrlen = sizeof(addr);
				SOCKET newClientSocket = accept(mSocket, reinterpret_cast<sockaddr*>(&addr), &addrlen);
				if (newClientSocket == INVALID_SOCKET)
					break;
				Client newClient;
				if (newClient.init(std::move(newClientSocket), addr))
				{
					auto message = std::make_unique<Messages::Connection>(Messages::Connection::Result::Success);
					message->idFrom = newClient.id();
					message->from = newClient.destinationAddress();
					mMessages.push_back(std::move(message));
					mClients[newClient.id()] = std::move(newClient);
				}
			}

			//!< mise à jour des clients connectés
			//!< réceptionne au plus 1 message par client
			//!< supprime de la liste les clients déconnectés
			for (auto itClient = mClients.begin(); itClient != mClients.end(); )
			{
				auto& client = itClient->second;
				auto msg = client.poll();
				if (msg)
				{
					msg->from = itClient->second.destinationAddress();
					msg->idFrom = itClient->second.id();
					if (msg->is<Messages::Disconnection>())
					{
						itClient = mClients.erase(itClient);
					}
					else
						++itClient;
					mMessages.push_back(std::move(msg));
				}
				else
					++itClient;
			}
		}
		bool ServerImpl::sendTo(uint64_t clientid, const unsigned char* data, unsigned int len)
		{
			auto itClient = mClients.find(clientid);
			return itClient != mClients.end() && itClient->second.send(data, len);
		}
		bool ServerImpl::sendToAll(const unsigned char* data, unsigned int len)
		{
			bool ret = true;
			for (auto& client : mClients)
				ret &= client.second.send(data, len);
			return ret;
		}
		std::unique_ptr<Messages::Base> ServerImpl::poll()
		{
			if (mMessages.empty())
				return nullptr;

			auto msg = std::move(mMessages.front());
			mMessages.pop_front();
			return msg;
		}
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		Server::Server() {}
		Server::~Server() {}
		Server::Server(Server&& other)
			: mImpl(std::move(other.mImpl))
		{}
		Server& Server::operator=(Server&& other)
		{
			mImpl = std::move(other.mImpl);
			return *this;
		}
		bool Server::start(unsigned short _port)
		{
			if (!mImpl)
				mImpl = std::make_unique<ServerImpl>();
			return mImpl && mImpl->start(_port);
		}
		void Server::stop() { if (mImpl) mImpl->stop(); }
		void Server::update() { if (mImpl) mImpl->update(); }
		bool Server::sendTo(uint64_t clientid, const unsigned char* data, unsigned int len) { return mImpl && mImpl->sendTo(clientid, data, len); }
		bool Server::sendToAll(const unsigned char* data, unsigned int len) { return mImpl && mImpl->sendToAll(data, len); }
		std::unique_ptr<Messages::Base> Server::poll() { return mImpl ? mImpl->poll() : nullptr; }
	}
>>>>>>> Stashed changes
}