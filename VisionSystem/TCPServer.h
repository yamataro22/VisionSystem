#pragma once
#include <WS2tcpip.h>	//header for winsock func
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

	//send a message to a specified client
	void sendMsg(int clientSocket, std::string msg);
	void sendMsg(int clientSocket, int* tab);

	//initialize winsock
	bool init();

	//the main processing loop
	void run();

	void cleanup();


private:
	//create a socket
	SOCKET createSocket();

	//wait for connection
	SOCKET waitForConnection(SOCKET listening);
 
	std::string					m_ipAdress;
	int							m_port;
	MessageReceivedHandler		MessageReceived;
};

