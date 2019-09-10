#pragma once
#include "Shape.h"
#include <cmath>

class BaseFrame :
	public Shape
{
public:
	BaseFrame(cv::Point2f ppintTab[]);
	~BaseFrame();
	void drawShape(cv::Mat& dst) override;
	double getXCoord(Point2f center);
	double getYCoord(Point2d center);
	double getWidth();
	double getHeight();
private:

	double getDistanceLinePoint(Point2f p1, Point2f p2, Point2f p3);
};
