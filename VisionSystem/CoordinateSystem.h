#pragma once
#include "Ksztalt.h"
class CoordinateSystem :	public Ksztalt
{
public:
	CoordinateSystem(cv::Point2f ppintTab[]);
	~CoordinateSystem();
	
	void drawShape(cv::Mat& dst) override;

private:
	void sortPoints(Point2f points[]);
	void showPoints(Point2f p[]);
	void drawCoordinateSystem(Mat& currentMat, Point2f tab[]);
	void giveCoordPoints(Point2f points[]);
};
