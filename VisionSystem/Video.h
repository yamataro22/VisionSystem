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

using coords = std::pair<double, double>;
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
	void startStreaming(std::shared_ptr<coords>);	
	void addJob(void (Video::*)());
	void addJob(jobs newJob);
	void clearJobs();

	~Video();

private:
	cv::Mat m_currentFrame;
	cv::Mat m_outputFrame;
	Calibration m_calibrator;
	cv::VideoCapture m_videoCap;
	std::vector <std::unique_ptr<Filter>> m_filTab;
	std::vector <void (Video::*)(void)> m_jobList;
	std::unique_ptr<coords> m_currentCoords;


	void checkIfOpened();
	void readFrame();
	void createFilTab();	//dodaje podstawowe filtry (gray, mBlur, thresh)
	void applyFilters();	
	bool waitForKey(int ms, int key);	//if true break
	void checkCoords(double scale);
	
};

