#pragma once
#include "Ksztalt.h"
#include <cmath>

class RamkaPodloza :
	public Ksztalt
{
public:
	RamkaPodloza(cv::Point2f ppintTab[]);
	~RamkaPodloza();
	void drawShape(cv::Mat& dst) override;
	double getXCoord(Point2f center);
	double getYCoord(Point2d center);
	double getWidth();
	double getHeight();
private:

	double getDistanceLinePoint(Point2f p1, Point2f p2, Point2f p3);
};

