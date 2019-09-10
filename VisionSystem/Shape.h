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

	virtual ~Shape() = default;
protected:
	vector<cv::Point2f> pointsTab;
	Point2f *pointsOld;
	int lineThicness = 8;
};

