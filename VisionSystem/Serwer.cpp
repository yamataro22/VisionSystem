#include "Serwer.h"



Serwer::Serwer()
{
	init();
}


Serwer::~Serwer()
{
	closesocket(clientSocket);
	WSACleanup();
}

void Serwer::init()
{
	WSADATA wsaData;
	int iResult;


	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		exit(1);
	}

	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "can't create socket" << endl;
		exit(1);
	}

	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(2000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, SOMAXCONN);

	sockaddr_in client;
	int clientSize = sizeof(client);

	clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
	char host[NI_MAXHOST];	//cient remote name
	char service[NI_MAXSERV]; //

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << "connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "connected on port " <<
			ntohs(client.sin_port) << endl;
	}

	closesocket(listening);

}

void Serwer::sendBytes(const char * bytesToSend)
{
	char buf[4096];

	send(clientSocket, bytesToSend, 23, 0);
	while (1)
	{
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "error in recv" << endl;
			break;
		}

		if (bytesReceived == 0)
		{
			cout << "cient disconnected " << endl;
			break;
		}
		cout << "otrzymano dane: " << buf << endl;
		//send(clientSocket, buf, bytesReceived + 1, 0);
	}
}
