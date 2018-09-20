#include "Kalibracja.h"




Kalibracja::Kalibracja():rgbParametry()
{
	
}

Kalibracja::~Kalibracja()
{
}

void Kalibracja::setSource(Mat& source)
{
	pCalib = source;
}

void Kalibracja::startCalibrationThreshold()
{
	checkIfEmpty(pCalib);
	configureTrackbar("thresh", &threshBinaryParam, 255, onThreshTrackbar, this);
	waitKey(0);
	destroyWindows();
}

void Kalibracja::startCalibrationBlur()
{
	checkIfEmpty(pCalib);
	configureTrackbar("blur", &blurParam, 8, onBlurTrackbar, this);
	waitKey(0);
	destroyWindows();
}

void Kalibracja::startCalibrationCanny()
{
	checkIfEmpty(pCalib);
	cannyParametry.cannyThresh = 30;
	configureTrackbar("thresh", &cannyParametry.cannyThresh, cannyParametry.cannyMaxThresh, onCannyThreshTrackbar, this);
	(waitKey(0)==2);
	destroyWindows();
}

void Kalibracja::startCalibrationRGBThreshold()
{
	checkIfEmpty(pCalib);
	configureTrackbar("lowR", &rgbParametry.low_r, 255, on_low_r_thresh_trackbar, this);
	configureTrackbar("highR", &rgbParametry.high_r, 255, on_high_r_thresh_trackbar, this);
	configureTrackbar("lowG", &rgbParametry.low_g, 255, on_low_g_thresh_trackbar, this);
	configureTrackbar("highG", &rgbParametry.high_g, 255, on_high_g_thresh_trackbar, this);
	configureTrackbar("lowB", &rgbParametry.low_b, 255, on_low_b_thresh_trackbar, this);
	configureTrackbar("highB", &rgbParametry.high_b, 255, on_high_b_thresh_trackbar, this);
	waitKey(0);
	destroyWindows();
}

void Kalibracja::showSource()
{
	imshow("source", pCalib);
}

void Kalibracja::configureTrackbar(const char * trackbarName, int* param, int maxVal, void func(int, void *), void * obj)
{
	namedWindow("trackbars", WINDOW_NORMAL);
	createTrackbar(trackbarName, "trackbars", param, maxVal, func, obj);
	func(0, this);
}

void Kalibracja::setGrayFilter(void* obj)
{
	Filtr fi;
	if (((Kalibracja*)obj)->pCalib.channels() == 1)	//jeœli jest w formacie jednokana³owym
		((Kalibracja*)obj)->pCalib.copyTo(((Kalibracja*)obj)->aCalib);
	else
		fi.filtr(filters::gray, ((Kalibracja*)obj)->pCalib, ((Kalibracja*)obj)->aCalib);
}

int Kalibracja::getBlurParam()
{
	mBlurStruct str;
	return str.value(blurParam);
}

int Kalibracja::getThreshParam()
{
	return threshBinaryParam;
}

cannyParams Kalibracja::getCannyParam()
{
	return cannyParametry;
}

threshRGBParams Kalibracja::getRGBParam()
{
	return rgbParametry;
}

void Kalibracja::checkIfEmpty(Mat & pic)
{
	if (pic.empty())
	{
		cout << "Nie udalo sie skalibrowac" << endl;
		exit(0);
	}
}

void Kalibracja::onThreshTrackbar(int, void * object)
{
	Kalibracja* myCalib = (Kalibracja*)object;
	setGrayFilter(myCalib);
	threshold(myCalib->aCalib, myCalib->aCalib, myCalib->threshBinaryParam, 255, 0);
	imshow("currentCalib", myCalib->aCalib);
}

void Kalibracja::onBlurTrackbar(int, void * object)
{
	Kalibracja* myCalib = (Kalibracja*)object;
	mBlurStruct blurStr;
	setGrayFilter(myCalib);
	medianBlur(myCalib->aCalib, myCalib->aCalib, blurStr.value((myCalib->blurParam)));
	imshow("currentCalib", myCalib->aCalib);
	
}

void Kalibracja::onCannyThreshTrackbar(int, void * object)
{
	Mat cannyOutput;
	Kalibracja* myCalib = (Kalibracja*)object;
	setGrayFilter(myCalib);

	Canny(myCalib->aCalib, cannyOutput, myCalib->cannyParametry.cannyThresh, 
		myCalib->cannyParametry.cannyThresh*myCalib->cannyParametry.cannyRatio, myCalib->cannyParametry.cannyKernel);
	imshow("currentCalib", cannyOutput);
}


void Kalibracja::on_low_r_thresh_trackbar(int, void *object)
{
	Kalibracja* myCalib = (Kalibracja*)object;
	Mat dst; 
	myCalib->rgbParametry.low_r = min(myCalib->rgbParametry.high_r - 1, myCalib->rgbParametry.low_r);
	inRange(myCalib->pCalib, Scalar(myCalib->rgbParametry.low_b, myCalib->rgbParametry.low_g, myCalib->rgbParametry.low_r)
		, Scalar(myCalib->rgbParametry.high_b, myCalib->rgbParametry.high_g, myCalib->rgbParametry.high_r), dst);
	imshow("currentCalib", dst);
}

void Kalibracja::on_high_r_thresh_trackbar(int, void *object)
{
	Kalibracja* myCalib = (Kalibracja*)object;
	Mat dst;
	myCalib->rgbParametry.high_r = max(myCalib->rgbParametry.high_r - 1, myCalib->rgbParametry.low_r);
	inRange(myCalib->pCalib, Scalar(myCalib->rgbParametry.low_b, myCalib->rgbParametry.low_g, myCalib->rgbParametry.low_r)
		, Scalar(myCalib->rgbParametry.high_b, myCalib->rgbParametry.high_g, myCalib->rgbParametry.high_r), dst);
	imshow("currentCalib", dst);
}

void Kalibracja::on_low_g_thresh_trackbar(int, void *object)
{
	Kalibracja* myCalib = (Kalibracja*)object;
	Mat dst;
	myCalib->rgbParametry.low_g = min(myCalib->rgbParametry.high_g - 1, myCalib->rgbParametry.low_g);
	inRange(myCalib->pCalib, Scalar(myCalib->rgbParametry.low_b, myCalib->rgbParametry.low_g, myCalib->rgbParametry.low_r)
		, Scalar(myCalib->rgbParametry.high_b, myCalib->rgbParametry.high_g, myCalib->rgbParametry.high_r), dst);
	imshow("currentCalib", dst);
}

void Kalibracja::on_high_g_thresh_trackbar(int, void *object)
{
	Kalibracja* myCalib = (Kalibracja*)object;
	Mat dst;
	myCalib->rgbParametry.high_g = max(myCalib->rgbParametry.high_g - 1, myCalib->rgbParametry.low_g);
	inRange(myCalib->pCalib, Scalar(myCalib->rgbParametry.low_b, myCalib->rgbParametry.low_g, myCalib->rgbParametry.low_r)
		, Scalar(myCalib->rgbParametry.high_b, myCalib->rgbParametry.high_g, myCalib->rgbParametry.high_r), dst);
	imshow("currentCalib", dst);
}

void Kalibracja::on_low_b_thresh_trackbar(int, void *object)
{
	Kalibracja* myCalib = (Kalibracja*)object;
	Mat dst;
	myCalib->rgbParametry.low_b = min(myCalib->rgbParametry.high_b - 1, myCalib->rgbParametry.low_b);
	inRange(myCalib->pCalib, Scalar(myCalib->rgbParametry.low_b, myCalib->rgbParametry.low_g, myCalib->rgbParametry.low_r)
		, Scalar(myCalib->rgbParametry.high_b, myCalib->rgbParametry.high_g, myCalib->rgbParametry.high_r), dst);
	imshow("currentCalib", dst);
}

void Kalibracja::on_high_b_thresh_trackbar(int, void *object)
{
	Kalibracja* myCalib = (Kalibracja*)object;
	Mat dst;
	myCalib->rgbParametry.high_b = max(myCalib->rgbParametry.high_b - 1, myCalib->rgbParametry.low_b);
	inRange(myCalib->pCalib, Scalar(myCalib->rgbParametry.low_b, myCalib->rgbParametry.low_g, myCalib->rgbParametry.low_r)
		, Scalar(myCalib->rgbParametry.high_b, myCalib->rgbParametry.high_g, myCalib->rgbParametry.high_r), dst);
	imshow("currentCalib", dst);
}


void Kalibracja::destroyWindows()
{
	destroyWindow("trackbars");
	destroyWindow("currentCalib");
}



