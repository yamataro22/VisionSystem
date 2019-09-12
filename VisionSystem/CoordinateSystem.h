#pragma once
#include "Shape.h"

class CoordinateSystem : public Shape
{
public:
	CoordinateSystem(cv::Point2f ppintTab[]);
	~CoordinateSystem();
	
	void drawShape(cv::Mat& dst) override;

private:
	void sortPoints();
	void showPoints();
    void setLowestPointToTheEndOfPointTab();
	void drawCoordinateSystem(Mat& currentMat, Point2f tab[]);

};

