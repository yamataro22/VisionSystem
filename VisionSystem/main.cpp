#pragma once

#include  "Video.h"
#include <thread>



int main()
{
	Video newVideo("http://192.168.88.74:8080/video?x.mjpeg");
	newVideo.clearJobs();
	newVideo.addJob(jobs::objectOnFrame);
	newVideo.startStreaming();

	return 0;
}


