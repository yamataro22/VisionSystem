#pragma once
#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Calibration.h"

class Filter;
class Contours;


#pragma comment (lib, "Ws2_32.lib")

#define SHEET_WIDTH  210
#define SHEET_HEIGHT  148

enum jobs { source, processed, contours, frame, coordinateSystem, objectOnFrame};

class Video
{
public:
	Video();
	Video(const char* IPadress);

	void calibrate();

	void processed();
	void source();
	void addContours();
	void addFrame();
	void addCoordinateSystem();
	void addObjectOnFrame();


	void addFilter(std::unique_ptr<Filter>);
	void clearFilTab();

	void startStreaming(double** message);	
	void addJob(void (Video::*)());
	void addJob(jobs newJob);
	void clearJobs();

	double* getCurrentCoords();
	~Video();

private:
	cv::Mat currentFrame;
	cv::Mat outputFrame;
	Calibration calib;
	cv::VideoCapture cap;
	std::vector <std::unique_ptr<Filter>> m_filTab;
	std::vector <void (Video::*)(void)> jobList;
	double* currentCoords;


	void checkIfOpened();
	void readFrame();
	void createFilTab();	//dodaje podstawowe filtry (gray, mBlur, thresh)
	void applyFilters();	
	bool waitForKey(int ms, int key);	//if true break
	void checkCoords(double scale);
	
};

