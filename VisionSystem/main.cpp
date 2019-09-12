#pragma once
#include "TCPServer.h"
#include  "Video.h"
#include <thread>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Defines.hpp"

using namespace cv;
using namespace std;

auto currentCoords = std::optional<Coords>();
std::mutex coordinateMutex;

void listenerMessageReceived(TCPServer* listener, int client, string msg);
void runServer();	

int main()
{
	thread threadServer(runServer);
	Video newVideo("http://192.168.88.74:8080/video?x.mjpeg");
	newVideo.calibrate();
	newVideo.clearJobs();
	newVideo.addJob(jobs::objectOnFrame);
	newVideo.startStreaming(*currentCoords, coordinateMutex);

	return 0;
}

void runServer()
{
	TCPServer server("192.168.0.1", 54000, listenerMessageReceived);
	if (server.init())
	{
		server.run();
	}
}

void listenerMessageReceived(TCPServer* listener, int client, string msg)
{
	cout << "Received: " << msg << endl;

	if (currentCoords && currentCoords->first < 210 and currentCoords->second < 150)
	{
		listener->sendMsg(client, *currentCoords);
		currentCoords = std::nullopt;
	}
	else
	{
		listener->sendMsg(client, "brak danych\n");
	}

}