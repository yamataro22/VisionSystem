#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
class Shape
{
public:
	Shape(cv::Point2f points[]);
	virtual void drawShape(cv::Mat& dst) {};
	virtual Point2f getCenterPoint()
	{
	    return Point2f(0,0);
	};
protected:
	vector<cv::Point2f> pointsTab;
	int lineThicness = 8;
};

