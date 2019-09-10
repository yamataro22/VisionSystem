#include "Calibration.h"
#include "Filter.h"
#include "GrayFilter.h"



Calibration::Calibration()
{
}

Calibration::~Calibration()
{
}

void Calibration::setSource(Mat& source)
{
	pCalib = source;
}

void Calibration::startCalibrationThreshold()
{
	checkIfEmpty(pCalib);
	configureTrackbar("thresh", &threshBinaryParam, 255, onThreshTrackbar, this);
	waitKey(0);
	destroyWindows();
}

void Calibration::startCalibrationBlur()
{
	checkIfEmpty(pCalib);
	configureTrackbar("blur", &blurParam, 8, onBlurTrackbar, this);
	waitKey(0);
	destroyWindows();
}

void Calibration::startCalibrationCanny()
{
	checkIfEmpty(pCalib);
	m_cannyParams.cannyThresh = 30;
	configureTrackbar("thresh", &m_cannyParams.cannyThresh, m_cannyParams.cannyMaxThresh, onCannyThreshTrackbar, this);
	(waitKey(0)==2);
	destroyWindows();
}

void Calibration::startCalibrationRGBThreshold()
{
	checkIfEmpty(pCalib);
	configureTrackbar("lowR",  &m_rgbThreshParams.low_r,  255, on_low_r_thresh_trackbar,  this);
	configureTrackbar("highR", &m_rgbThreshParams.high_r, 255, on_high_r_thresh_trackbar, this);
	configureTrackbar("lowG",  &m_rgbThreshParams.low_g,  255, on_low_g_thresh_trackbar,  this);
	configureTrackbar("highG", &m_rgbThreshParams.high_g, 255, on_high_g_thresh_trackbar, this);
	configureTrackbar("lowB",  &m_rgbThreshParams.low_b,  255, on_low_b_thresh_trackbar,  this);
	configureTrackbar("highB", &m_rgbThreshParams.high_b, 255, on_high_b_thresh_trackbar, this);
	waitKey(0);
	destroyWindows();
}

void Calibration::showSource()
{
	imshow("source", pCalib);
}

void Calibration::configureTrackbar(const char * trackbarName, int* param, int maxVal, void func(int, void *), void * obj)
{
	namedWindow("trackbars", WINDOW_NORMAL);
	createTrackbar(trackbarName, "trackbars", param, maxVal, func, obj);
	func(0, this);
}

void Calibration::setGrayFilter(void* obj)
{
	GrayFilter l_grayFilter;

	if (((Calibration*)obj)->pCalib.channels() == 1)	//jeœli jest w formacie jednokana³owym
		((Calibration*)obj)->pCalib.copyTo(((Calibration*)obj)->aCalib);
	else
		l_grayFilter.filtr(((Calibration*)obj)->pCalib, ((Calibration*)obj)->aCalib);
}

int Calibration::getBlurParam()
{
	mBlurStruct str;
	return str.value(blurParam);
}

int Calibration::getThreshParam()
{
	return threshBinaryParam;
}

CannyParameters & Calibration::getCannyParams()
{
	return m_cannyParams;
}

void Calibration::checkIfEmpty(Mat & pic)
{
	if (pic.empty())
	{
		cout << "Nie udalo sie skalibrowac" << endl;
		exit(0);
	}
}

void Calibration::onThreshTrackbar(int, void * object)
{
	Calibration* myCalib = (Calibration*)object;
	setGrayFilter(myCalib);
	threshold(myCalib->aCalib, myCalib->aCalib, myCalib->threshBinaryParam, 255, 0);
	imshow("currentCalib", myCalib->aCalib);
}

void Calibration::onBlurTrackbar(int, void * object)
{
	Calibration* myCalib = (Calibration*)object;
	mBlurStruct blurStr;
	setGrayFilter(myCalib);
	medianBlur(myCalib->aCalib, myCalib->aCalib, blurStr.value((myCalib->blurParam)));
	imshow("currentCalib", myCalib->aCalib);
	
}

void Calibration::onCannyThreshTrackbar(int, void * object)
{
	Mat cannyOutput;
	Calibration* myCalib = (Calibration*)object;
	setGrayFilter(myCalib);

	Canny(myCalib->aCalib, cannyOutput, myCalib->m_cannyParams.cannyThresh,
		myCalib->m_cannyParams.cannyThresh*myCalib->m_cannyParams.cannyRatio, myCalib->m_cannyParams.cannyKernel);
	imshow("currentCalib", cannyOutput);
}


void Calibration::on_low_r_thresh_trackbar(int, void *object)
{
	Calibration* myCalib = (Calibration*)object;
	Mat dst; 
	myCalib->m_rgbThreshParams.low_r = min(myCalib->m_rgbThreshParams.high_r - 1, myCalib->m_rgbThreshParams.low_r);
	inRange(myCalib->pCalib, Scalar(myCalib->m_rgbThreshParams.low_b, myCalib->m_rgbThreshParams.low_g, myCalib->m_rgbThreshParams.low_r)
		, Scalar(myCalib->m_rgbThreshParams.high_b, myCalib->m_rgbThreshParams.high_g, myCalib->m_rgbThreshParams.high_r), dst);
	imshow("currentCalib", dst);
}

void Calibration::on_high_r_thresh_trackbar(int, void *object)
{
	Calibration* myCalib = (Calibration*)object;
	Mat dst;
	myCalib->m_rgbThreshParams.high_r = max(myCalib->m_rgbThreshParams.high_r - 1, myCalib->m_rgbThreshParams.low_r);
	inRange(myCalib->pCalib, Scalar(myCalib->m_rgbThreshParams.low_b, myCalib->m_rgbThreshParams.low_g, myCalib->m_rgbThreshParams.low_r)
		, Scalar(myCalib->m_rgbThreshParams.high_b, myCalib->m_rgbThreshParams.high_g, myCalib->m_rgbThreshParams.high_r), dst);
	imshow("currentCalib", dst);
}

void Calibration::on_low_g_thresh_trackbar(int, void *object)
{
	Calibration* myCalib = (Calibration*)object;
	Mat dst;
	myCalib->m_rgbThreshParams.low_g = min(myCalib->m_rgbThreshParams.high_g - 1, myCalib->m_rgbThreshParams.low_g);
	inRange(myCalib->pCalib, Scalar(myCalib->m_rgbThreshParams.low_b, myCalib->m_rgbThreshParams.low_g, myCalib->m_rgbThreshParams.low_r)
		, Scalar(myCalib->m_rgbThreshParams.high_b, myCalib->m_rgbThreshParams.high_g, myCalib->m_rgbThreshParams.high_r), dst);
	imshow("currentCalib", dst);
}

void Calibration::on_high_g_thresh_trackbar(int, void *object)
{
	Calibration* myCalib = (Calibration*)object;
	Mat dst;
	myCalib->m_rgbThreshParams.high_g = max(myCalib->m_rgbThreshParams.high_g - 1, myCalib->m_rgbThreshParams.low_g);
	inRange(myCalib->pCalib, Scalar(myCalib->m_rgbThreshParams.low_b, myCalib->m_rgbThreshParams.low_g, myCalib->m_rgbThreshParams.low_r)
		, Scalar(myCalib->m_rgbThreshParams.high_b, myCalib->m_rgbThreshParams.high_g, myCalib->m_rgbThreshParams.high_r), dst);
	imshow("currentCalib", dst);
}

void Calibration::on_low_b_thresh_trackbar(int, void *object)
{
	Calibration* myCalib = (Calibration*)object;
	Mat dst;
	myCalib->m_rgbThreshParams.low_b = min(myCalib->m_rgbThreshParams.high_b - 1, myCalib->m_rgbThreshParams.low_b);
	inRange(myCalib->pCalib, Scalar(myCalib->m_rgbThreshParams.low_b, myCalib->m_rgbThreshParams.low_g, myCalib->m_rgbThreshParams.low_r)
		, Scalar(myCalib->m_rgbThreshParams.high_b, myCalib->m_rgbThreshParams.high_g, myCalib->m_rgbThreshParams.high_r), dst);
	imshow("currentCalib", dst);
}

void Calibration::on_high_b_thresh_trackbar(int, void *object)
{
	Calibration* myCalib = (Calibration*)object;
	Mat dst;
	myCalib->m_rgbThreshParams.high_b = max(myCalib->m_rgbThreshParams.high_b - 1, myCalib->m_rgbThreshParams.low_b);
	inRange(myCalib->pCalib, Scalar(myCalib->m_rgbThreshParams.low_b, myCalib->m_rgbThreshParams.low_g, myCalib->m_rgbThreshParams.low_r)
		, Scalar(myCalib->m_rgbThreshParams.high_b, myCalib->m_rgbThreshParams.high_g, myCalib->m_rgbThreshParams.high_r), dst);
	imshow("currentCalib", dst);
}


void Calibration::destroyWindows()
{
	destroyWindow("trackbars");
	destroyWindow("currentCalib");
}



