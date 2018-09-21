#include "Video.h"



Video::Video()
{
	createFilTab();
	cap.open("http://192.168.1.10:8080/video?x.mjpeg");
	checkIfOpened();
	jobList.push_back(&Video::source);
	jobList.push_back(&Video::processed);
}

Video::Video(const char * IPadress)
{
	createFilTab();
	cap.open(IPadress);
	checkIfOpened();
	jobList.push_back(&Video::source);
	jobList.push_back(&Video::processed);
}

void Video::calibrate()
{
	readFrame();
	fil.filtr(filters::mBlur, currentFrame);
	calib.setSource(currentFrame);
	calib.startCalibrationThreshold();
	fil.setThreshBinaryParam(calib.getThreshParam());
	fil.filtr(threshBinary, currentFrame);
	calib.startCalibrationCanny();
	fil.setCannyParams(calib.getCannyParam());
}

void Video::processed()
{
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);
	applyFilters();
	imshow("MyVideo", outputFrame);
}

void Video::source()
{
	namedWindow("MySource", CV_WINDOW_AUTOSIZE);
	imshow("MySource", currentFrame);
}

void Video::addFilter(filters fil)
{
	filTab.push_back(fil);
}


void Video::clearFilTab()
{
	filTab.clear();
}

void Video::startStreaming()
{
	while (1)
	{
		readFrame();
		for (int i = 0; i < jobList.size(); i++)
			(this->*jobList[i])();
		if (waitForKey(30, 27))
			break;
	}
}

void Video::addJob(void (Video::*f)())
{
	jobList.push_back(f);
}

void Video::addJob(jobs newJob)
{
	switch (newJob)
	{
	case 0:
		addJob(&Video::source);
		break;
	case 1:
		addJob(&Video::processed);
		break;
	case 2:
		addJob(&Video::findContours);
		break;
	case 3:
		addJob(&Video::drawFrame);
	}
}

void Video::clearJobs()
{
	jobList.clear();
}

void Video::findContours()
{
	ContourCreator contours;
	namedWindow("contours", CV_WINDOW_AUTOSIZE);
	applyFilters();
	Mat dst;
	contours.drawContours(outputFrame, dst);
	imshow("contours", dst);	
}

void Video::drawFrame()
{
	Mat dst;
	ContourCreator frameContours;
	namedWindow("frame", CV_WINDOW_AUTOSIZE);
	applyFilters();
	frameContours.drawFrameRectangle(outputFrame, dst);
	imshow("contours", dst);
}


Video::~Video()
{
}

void Video::checkIfOpened()
{
	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		exit(1);
	}
}

void Video::readFrame()
{
	bool bSuccess = cap.read(currentFrame); // read a new frame from video
	if (!bSuccess) //if not success, break loop
	{
		cout << "Cannot read a frame from video stream" << endl;
		exit(1);
	}
}

void Video::createFilTab()
{
	filTab.push_back(gray);
	filTab.push_back(mBlur);
	filTab.push_back(filters::threshBinary);
	filTab.push_back(filters::canny);

}

void Video::applyFilters()
{
	currentFrame.copyTo(outputFrame);
	for (int i = 0; i < filTab.size(); i++)
	{
		fil.filtr(filTab[i], outputFrame);
	}
}

bool Video::waitForKey(int ms, int key)
{
	if (waitKey(ms) == key) 
	{
		cout << "esc key is pressed by user" << endl;
		return true;
	}
	return false;
}


