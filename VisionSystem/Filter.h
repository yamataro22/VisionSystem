#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

enum filters{gray,mBlur,threshBinary,gauss,sharpen,threshRGB, canny};

struct sobelParams {
	int ddepth; //g³êbia obrazu
	int ksize;
	int delta;
	int scale;

	sobelParams(int ddep, int ksiz, int del, int sc);
};



class Filter
{
public:
	
	Filter();
	~Filter();

	static void determineType(Mat& src);
	virtual void filtr(Mat& src) = 0;
	virtual void filtr(const Mat& src, Mat& dst) = 0;	
	void sobel(Mat& src, Mat& dst);
	void sobel(Mat & src, Mat & dst, sobelParams);

	void setgBlurParam(int newParam);

private:

	Mat currentCalib;
	int gBlurMSize;

	void gBlur(Mat& src);
	void gBlur(const Mat& src, Mat& dst);
	void sharp(Mat& src);
	void sharp(const Mat& src, Mat& dst);
};


