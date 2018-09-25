#pragma once

#include "Kontury.h"
#include "Kalibracja.h"
#include "Filtr.h"

#pragma comment (lib, "Ws2_32.lib")


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


	void addFilter(filters);
	void clearFilTab();

	void startStreaming();	
	void addJob(void (Video::*)());
	void addJob(jobs newJob);
	void clearJobs();

	double* getCurrentCoords();
	~Video();

private:
	Mat currentFrame;
	Mat outputFrame;
	Kalibracja calib;
	Filtr fil;
	VideoCapture cap;
	vector <filters> filTab;
	vector <void (Video::*)(void)> jobList;
	double* currentCoords;


	void checkIfOpened();
	void readFrame();
	void createFilTab();	//dodaje podstawowe filtry (gray, mBlur, thresh)
	void applyFilters();	
	bool waitForKey(int ms, int key);	//if true break
	
};

