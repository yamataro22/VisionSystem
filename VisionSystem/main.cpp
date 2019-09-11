#pragma once
#include "TCPServer.h"
#include  "Video.h"
#include <thread>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

using coords = std::pair<double, double>;
std::shared_ptr<coords> currentCoords = std::make_shared<coords>(std::make_pair<double,double>(0.,0.));

void listenerMessageReceived(TCPServer* listener, int client, string msg);
std::string toHex(const std::string& s, bool upper_case = true);
void runServer();	

int main()
{
	thread threadServer(runServer);
	Video newVideo("http://192.168.88.74:8080/video?x.mjpeg");
	newVideo.calibrate();
	newVideo.clearJobs();
	newVideo.addJob(jobs::objectOnFrame);
	newVideo.startStreaming(currentCoords);

	return 0;
}


std::string toHex(const string& s, bool upper_case)
{
	ostringstream ret;

	for (string::size_type i = 0; i < s.length(); ++i)
		ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];
	ret << std::hex << "0D" << "0A";
	return ret.str();
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

	if (currentCoords != nullptr and currentCoords->first < 210 and currentCoords->second < 150)
	{
		int tab[2];
		tab[0] = static_cast<int>(currentCoords->first);
		tab[1] = static_cast<int>(currentCoords->first);
		listener->sendMsg(client, tab);
	}
	else
	{
		int tab[2] = { 0,0 };
		listener->sendMsg(client, "brak danych\n");
	}

}