#pragma once

#include  "Video.h"
//#include "Serwer.h"
#include <thread>

int main()
{
	Video newVideo("http://192.168.1.18:8080/video?x.mjpeg");
	newVideo.clearJobs();
	//newVideo.addJob(source);
	newVideo.addJob(frame);

	newVideo.startStreaming();

	return 0;
}


