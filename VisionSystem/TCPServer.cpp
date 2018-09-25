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
	send(clientSocket, msg.c_str(), msg.size() + 1, 0);
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
		inet_pton(AF_INET, m_ipAdress.c_str(), &hint.sin_addr);

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
	SOCKET client = accept(listening, NULL, NULL);
	return client;
}



