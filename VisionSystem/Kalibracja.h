#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include "Filtr.h"


using namespace cv;
using namespace std;

class Kalibracja
{
public:

	Kalibracja();
	~Kalibracja();

	void setSource(Mat& source);
	void startCalibrationThreshold();
	void startCalibrationBlur();
	void startCalibrationCanny();
	void startCalibrationRGBThreshold();
	void showSource();
	int getBlurParam();
	int getThreshParam();
	cannyParams getCannyParam();
	threshRGBParams getRGBParam();

private:


	Mat pCalib;
	Mat aCalib;
	int threshBinaryParam = 120;
	int blurParam = 0;
	cannyParams cannyParametry;
	threshRGBParams rgbParametry;
	

	void configureTrackbar(const char* trackbarName, int* param, int maxVal, void func(int, void*), void* obj); //dodanie trackbaru do okna i koniguracja parametrów
	static void setGrayFilter(void* obj);

	void checkIfEmpty(Mat& pic);
	static void onThreshTrackbar(int, void* obj);
	static void onBlurTrackbar(int, void* obj);
	static void onCannyThreshTrackbar(int, void*);
	static void on_low_r_thresh_trackbar(int, void *);
	static void on_high_r_thresh_trackbar(int, void *);
	static void on_low_g_thresh_trackbar(int, void *);
	static void on_high_g_thresh_trackbar(int, void *);
	static void on_low_b_thresh_trackbar(int, void *);
	static void on_high_b_thresh_trackbar(int, void *);

	void destroyWindows();

	struct mBlurStruct
	{
		int minVal = 3;
		int maxVal = 11;
		int res = 2;

		int range()
		{
			return maxVal - minVal;
		}
		int ticks()
		{
			return range() / res;
		}
		int value(int param)
		{
			return minVal + param * range() / ticks();
		}
	};

};

