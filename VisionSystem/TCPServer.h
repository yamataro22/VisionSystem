#pragma once
#include <WS2tcpip.h>	//header for winsock func
#include "Defines.hpp"
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")	//winsock library file

#define MAX_BUFFER_SIZE (49152)
class TCPServer;

typedef void (*MessageReceivedHandler)(TCPServer* listener, int socketId, std::string message);

class TCPServer
{

public:
	TCPServer(std::string ipAdress, int port, MessageReceivedHandler);
	~TCPServer();
	void sendMsg(int clientSocket, std::string msg);
	void sendMsg(int clientSocket, Coords&);
	bool init();
	void run();
	void cleanup();

private:

	SOCKET createSocket();
	SOCKET waitForConnection(SOCKET listening);
 
	std::string					m_ipAdress;
	int							m_port;
	MessageReceivedHandler		MessageReceived;
};

