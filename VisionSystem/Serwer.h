#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "Ws2_32.lib")

class Serwer
{
public:
	Serwer();
	~Serwer();
	
	void sendBytes(const char* bytesToSend);
private:
	SOCKET clientSocket;
	SOCKET listening;
	void init();
};



//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "2000"


/*int main(void)
{
	WSADATA wsaData;
	int iResult;


	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "can't create socket" << endl;
		return 0;
	}

	struct sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(2000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, SOMAXCONN);

	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
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

	char buf[4096];
	const char* text = "244C6F67696E2C61616103";

	send(clientSocket, text, 23, 0);
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

	// cleanup
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}
*/