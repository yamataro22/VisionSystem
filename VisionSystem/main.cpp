#pragma once
#include "TCPServer.h"
#include  "Video.h"

#include <thread>
double* currentCoords;

void listenerMessageReceived(TCPServer* listener, int client, string msg);
int main()
{
	TCPServer server("127.0.0.1", 2000, listenerMessageReceived);
	if (server.init())
	{
		server.run();
	}

	//Video newVideo("http://192.168.88.74:8080/video?x.mjpeg");	
	//newVideo.calibrate();
	//newVideo.clearJobs();
	//newVideo.addJob(jobs::objectOnFrame);
	//newVideo.startStreaming();
	return 0;
}

void listenerMessageReceived(TCPServer* listener, int client, string msg)
{
	listener->sendMsg(client, msg);
}

