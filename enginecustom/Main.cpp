#include "TCPSocket.hpp"

#include <iostream>

int main()
{
	if (!Sockets::Start())
	{
		std::cout << "Erreur initialisation : " << Sockets::GetError() << std::endl;
		return 0;
	}

	{
		TCPSocket socket;
		if (!socket.Connect("127.0.0.1", 6666))
		{
			std::cout << "Erreur connection : " << Sockets::GetError() << std::endl;
			return 0;
		}
		std::cout << "Socket connecte !" << std::endl;
	}
	Sockets::Release();
}