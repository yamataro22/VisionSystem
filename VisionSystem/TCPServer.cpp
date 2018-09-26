#include "TCPServer.h"



TCPServer::TCPServer(std::string ipAdress, int port, MessageReceivedHandler handler)
	: m_ipAdress(ipAdress), m_port(port), MessageReceived(handler)
{

}

TCPServer::~TCPServer()
{
	cleanup();
}

void TCPServer::sendMsg(int clientSocket, std::string msg)
{
	send(clientSocket, msg.c_str(), msg.size(), 0);
}

bool TCPServer::init()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	INT wsInit = WSAStartup(ver, &data);

	//TODO inform caller that the error that occured

	return wsInit == 0;
}

void TCPServer::run()
{
	char buf[MAX_BUFFER_SIZE];
	while (true)
	{
		//create a listening socket
		SOCKET listening = createSocket();
		if (listening == INVALID_SOCKET)
		{
			break;
		}
		SOCKET client = waitForConnection(listening);
		if (client != INVALID_SOCKET)
		{
			std::cout << "polaczono z klientem" << std::endl;
			closesocket(listening);
			int bytesReceived = 0;
			do
			{
				ZeroMemory(buf, MAX_BUFFER_SIZE);

				bytesReceived = recv(client, buf, MAX_BUFFER_SIZE, 0);
				if (bytesReceived > 0)
				{
					if (MessageReceived != NULL)
					{
						MessageReceived(this, client, std::string(buf, 0, bytesReceived));
					}
				}
	
			} while (bytesReceived > 0);

			closesocket(client);
			std::cout << "rozlaczono" << std::endl;
			//wait for a connection
			//loop receive/send
		}


	}
}

void TCPServer::cleanup()
{
	WSACleanup();
}

SOCKET TCPServer::createSocket()
{
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening != INVALID_SOCKET)
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(m_port);
		hint.sin_addr.S_un.S_addr = INADDR_ANY;

		int bindOk = bind(listening, (sockaddr*)&hint, sizeof(hint));
		if (bindOk != SOCKET_ERROR)
		{
			int listenOk = listen(listening, SOMAXCONN);
			if (listenOk == SOCKET_ERROR)
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}	
	}
	return listening;
}

SOCKET TCPServer::waitForConnection(SOCKET listening)
{
	sockaddr_in clientAddr;
	int clientSize = sizeof(clientAddr);
	SOCKET client = accept(listening, (sockaddr*)&clientAddr, &clientSize);
	char host[NI_MAXHOST];
	char service[NI_MAXHOST];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&clientAddr, sizeof(clientAddr), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << "connection on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &clientAddr.sin_addr, host, NI_MAXHOST);
		std::cout << host << "connection on port " << ntohs(clientAddr.sin_port) << std::endl;
	}

	return client;
}



