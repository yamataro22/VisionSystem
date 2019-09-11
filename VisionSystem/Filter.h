#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;


class Filter
{
public:
	
	Filter();
	~Filter();

	static void determineType(Mat& src);
	virtual void filtr(Mat& src) = 0;
	virtual void filtr(const Mat& src, Mat& dst) = 0;	

	void setgBlurParam(int newParam);

private:

	Mat m_currentCalib;
	int gBlurMSize;

	void gBlur(Mat& src);
	void gBlur(const Mat& src, Mat& dst);
	void sharp(Mat& src);
	void sharp(const Mat& src, Mat& dst);
};


