#pragma once
#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Calibration.h"
#include "Defines.hpp"
#include <optional>
#include <mutex>

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
	void startStreaming(Coords&, std::mutex& p_mutex);
	void addJob(void (Video::*)());
	void addJob(jobs newJob);
	void clearJobs();

private:
	cv::Mat m_currentFrame;
	cv::Mat m_outputFrame;
	Calibration m_calibrator;
	cv::VideoCapture m_videoCap;
	std::vector <std::unique_ptr<Filter>> m_filTab;
	std::vector <void (Video::*)(void)> m_jobList;
	std::optional<Coords> m_currentCoords;

	void checkIfOpened();
	void readFrame();
	void createFiltersTab();	//adds basic filters
	void applyFilters();	
	bool waitForKey(int ms, int key);	//if true break
	void checkCoords(double scale);
};

