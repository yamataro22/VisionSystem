#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
using coordPair = std::pair<double, double>;
class Shape;
class CoordinateSystem;
class RectangularShare;
class BaseFrame;


class ContourCreator
{
public:
	ContourCreator(const cv::Mat&);
	~ContourCreator();

	void addFrame();
	void addCoordinateSystem();
	void addObject();
	void addAllRectangles();

	void addText(cv::Mat&, const char*);

	void drawShapes(cv::Mat&);
	void drawContoursOnly(cv::Mat&);
	std::unique_ptr<coordPair> getRelativeObjectCoords();
	std::unique_ptr<coordPair> getAbsoluteObjectCoords(double, double);

private:

	cv::Mat src;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::RotatedRect> minRect;
	std::vector<Shape*> shapesToDraw;
	Shape* objToDraw;
	cv::Point2f centerCoords;

	void findContours();
	void* findRectangles();
	void updateCenterCoords(cv::Point2f*);

	static int getBiggestRectangleIndex(const std::vector<cv::RotatedRect>&,
										const std::vector<std::vector<cv::Point>>&);

	void sortByArea(std::vector<cv::RotatedRect>);
	void eliminateDuplicates(std::vector<cv::RotatedRect>&, int, int);
	std::unique_ptr<coordPair> getFrameScale(double, double);
};

