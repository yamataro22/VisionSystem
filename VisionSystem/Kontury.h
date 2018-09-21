#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include "Ksztalt.h"
#include "RamkaPodloza.h"
#include "CoordinateSystem.h"

using namespace cv;
using namespace std;

class ContourCreator
{
public:
	ContourCreator();
	~ContourCreator();

	void drawContours(const Mat& src, Mat& dst);
	void addText(Mat& src, const char* textToAdd);
	void drawFrameRectangle(const Mat& src, Mat& dst);
	void drawCoordinateSystem(const Mat& src, Mat & dst);
private:
	vector<vector<Point> > contours;
	vector<RotatedRect> minRect;
	vector<Ksztalt> shapesToDraw;
	void findContours(const Mat& src);
	void findRectangles(const Mat& src);
	void drawContoursToDst(Mat& dst);
	void drawShapes(Mat & dst);
	static int getFrameRectangleIndex(const vector<RotatedRect> &boundRect, const vector<vector<Point>>& contours);
	
};

