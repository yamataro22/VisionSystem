#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;


class Filter
{
public:

	virtual void filtr(Mat& src) = 0;
	virtual void filtr(const Mat& src, Mat& dst) = 0;	

private:

	Mat m_currentCalib;
};


