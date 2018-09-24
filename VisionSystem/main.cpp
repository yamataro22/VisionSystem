#pragma once

#include  "Video.h"
//#include "Serwer.h"
#include <thread>

int main()
{
	Video newVideo("http://192.168.1.18:8080/video?x.mjpeg");
	newVideo.calibrate();
	newVideo.clearJobs();
	newVideo.addJob(jobs::objectOnFrame);
	newVideo.startStreaming();

	return 0;
}


