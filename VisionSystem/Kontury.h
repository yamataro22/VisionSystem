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
	ContourCreator(const Mat& src, Mat& dst);
	~ContourCreator();
	//this is additional line in classessRefactor
	//and another 1
	static void drawContours(const Mat& src, Mat& dst);
	static void addText(Mat& src, const char* textToAdd);
	void drawFrameRectangle(const Mat& src, Mat& dst);
private:
	vector<Ksztalt> shapesToDraw;
	static int getFrameRectangleIndex(const vector<RotatedRect> &boundRect, const vector<vector<Point>>& contours);
	
	/*
	static void giveCoordPoints(Point2f points[]);
	static void sortPoints(Point2f points[]);
	static void showPoints(Point2f p[]);
	static void drawCoordinateSystem(Mat& currentMat, Point2f tab[]);
	*/

};

