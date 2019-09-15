#pragma once
#include "Shape.h"
#include <vector>
#include <cmath>

class BaseFrame :
	public Shape
{
public:
	BaseFrame(cv::Point2f ppintTab[]);
	void drawShape(cv::Mat& dst) override;
	double getXCoord(Point2f center);
	double getYCoord(Point2d center);
	double getWidth();
	double getHeight();
private:
	double getDistanceLinePoint(Point2f, Point2f, Point2f);
    void sortVectorByXAscending(std::vector<Point2f>&);
    void sortVectorByYDescending(std::vector<Point2f>&);
};

