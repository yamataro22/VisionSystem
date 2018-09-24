#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include "Ksztalt.h"
#include "RamkaPodloza.h"
#include "CoordinateSystem.h"
#include "ObiektProstokatny.h"

using namespace cv;
using namespace std;

class ContourCreator
{
public:
	ContourCreator(const Mat& src);
	~ContourCreator();

	void addFrame();	//adds frame to joblist; drawShapes to execute
	void addCoordinateSystem();
	void addObject();
	void addAllRectangles();

	void addText(Mat& src, const char* textToAdd);

	void drawShapes(Mat& dst);
	void drawContoursOnly(Mat& dst);
	double* getObjectRecativeCoords(Point2f* framePoints);
private:
	typedef unique_ptr<Ksztalt> shapePtr;

	Mat src;
	vector<vector<Point> > contours;
	vector<RotatedRect> minRect;
	vector<shapePtr> shapesToDraw;
	unique_ptr<Ksztalt> objectToMove;
	void findContours();
	void findRectangles();


	static int getBiggestRectangleIndex(const vector<RotatedRect> &boundRect, const vector<vector<Point>>& contours);
	void sortByArea(vector<RotatedRect> rectangles);
	void eliminateDuplicates(vector<RotatedRect>& rectangles, int frameIndex, int percentError);
};

