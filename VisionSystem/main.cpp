#pragma once
#include "TCPServer.h"
#include  "Video.h"

#include <thread>
double* currentCoords;

void listenerMessageReceived(TCPServer* listener, int client, string msg);
string toHex(const string& s, bool upper_case = true);
void runServer();	
void runVisionSystem();

int main()
{
	thread threadServer(runServer);
	Video newVideo("http://192.168.88.74:8080/video?x.mjpeg");
	newVideo.calibrate();
	newVideo.clearJobs();
	newVideo.addJob(jobs::objectOnFrame);
	newVideo.startStreaming(&currentCoords);

	return 0;
}


string toHex(const string& s, bool upper_case)
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

void runVisionSystem()
{
	Video newVideo("http://192.168.43.1:8080/video?x.mjpeg");
	newVideo.calibrate();
	newVideo.clearJobs();
	newVideo.addJob(jobs::objectOnFrame);
	newVideo.startStreaming(&currentCoords);
}

void listenerMessageReceived(TCPServer* listener, int client, string msg)
{

	cout << "Otrzymano: " << msg << endl;
	string message;
	string messageToSend;

	message += to_string(static_cast<int>(20));
	message += ",";
	message += to_string(static_cast<int>(20));
	messageToSend = toHex(message);
	
	cout << "wyslano: " << messageToSend << endl;

	listener->sendMsg(client, messageToSend);
	/*
	if (currentCoords != nullptr)
	{
		string message;
		message += to_string(static_cast<int>(currentCoords[0]));
		message += ",";
		message += to_string(static_cast<int>(currentCoords[1]));

		listener->sendMsg(client, toHex(message));
	}
	else
	{
		listener->sendMsg(client, "brak danych\n");
	}
	*/
}