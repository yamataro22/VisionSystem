#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

enum filters{gray,mBlur,threshBinary,gauss,sharpen,threshRGB, canny};

struct cannyParams
{
	int cannyThresh;
	const int cannyMaxThresh = 100;
	int cannyRatio;
	int	cannyKernel;

	cannyParams();
	cannyParams(int, int, int);
};

struct sobelParams {
	int ddepth; //g³êbia obrazu
	int ksize;
	int delta;
	int scale;

	sobelParams(int ddep, int ksiz, int del, int sc);
};

struct threshRGBParams
{
	int low_r, low_g, low_b;
	int high_r, high_g, high_b;

	threshRGBParams(int, int, int, int, int, int);
	threshRGBParams();
};

class Filtr
{
public:
	
	Filtr();
	~Filtr();

	static void determineType(Mat& src);
	void filtr(filters which, Mat& src);
	void filtr(filters which, Mat& src, Mat& dst);	
	void sobel(Mat& src, Mat& dst);
	void sobel(Mat & src, Mat & dst, sobelParams);
	void canny(Mat& src, Mat& dst);
	void canny(Mat& src, Mat& dst, cannyParams);

	void setmBlurParam(int newParam);
	void setgBlurParam(int newParam);
	void setThreshBinaryParam(int newParam);
	void setThreshRGBParams(int, int, int, int, int, int);
	void setThreshRGBParams(threshRGBParams newParams);
	void setCannyParams(cannyParams newParams);

private:

	Mat currentCalib;

	int mBlurParam;
	int gBlurMSize;
	int threshBinaryParam;
	threshRGBParams threshRGBParam;
	cannyParams cannyParam;


	void gray(Mat& src);
	void gray(const Mat& src, Mat& dst);
	void thresh(Mat& src);
	void thresh(const Mat& src, Mat& dst);
	void mBlur(Mat& src);
	void mBlur(const Mat& src, Mat& dst);
	void gBlur(Mat& src);
	void gBlur(const Mat& src, Mat& dst);
	void sharp(Mat& src);
	void sharp(const Mat& src, Mat& dst);
	void threshColor(Mat& src); 
	void threshColor(const Mat& src, Mat& dst);
	void canny(Mat& src);
};


