#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>

class Shape;
class CoordinateSystem;
class RectangularShare;
class BaseFrame;


class ContourCreator
{
public:
	ContourCreator(const cv::Mat&);
	~ContourCreator();

	void addFrame();	//adds frame to joblist; drawShapes to execute
	void addCoordinateSystem();
	void addObject();
	void addAllRectangles();

	void addText(cv::Mat& src, const char* textToAdd);

	void drawShapes(cv::Mat& dst);
	void drawContoursOnly(cv::Mat& dst);
	double *getRelativeObjectCoords();
	double* getAbsoluteObjectCoords(double width, double height);

private:
	//typedef unique_ptr<Ksztalt> shapePtr;

	cv::Mat src;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::RotatedRect> minRect;
	std::vector<Shape*> shapesToDraw;
	Shape* objToDraw;
	cv::Point2f centerCoords;

	void findContours();
	void* findRectangles();
	void updateCenterCoords(cv::Point2f* framePoints);


	static int getBiggestRectangleIndex(const std::vector<cv::RotatedRect> &boundRect,
										const std::vector<std::vector<cv::Point>>& contours);
	void sortByArea(std::vector<cv::RotatedRect> rectangles);
	void eliminateDuplicates(std::vector<cv::RotatedRect>& rectangles, int frameIndex, int percentError);
	double * getFrameScale(double width, double height);
};

