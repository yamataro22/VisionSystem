#include "BaseFrame.h"





BaseFrame::BaseFrame(cv::Point2f ppintTab[]) : Shape(ppintTab)
{	
}

BaseFrame::~BaseFrame()
{
}

void BaseFrame::drawShape(cv::Mat & src)
{
	for (int j = 0; j < 4; j++)
	{
		line(src, pointsTab[j], pointsTab[(j + 1) % 4], Scalar(0, 255, 0));
	}
}

double BaseFrame::getXCoord(Point2f center)
{
	vector<Point2f> tempTab = pointsTab;

	for (int i = 0; i < tempTab.size() - 1; i++)
	{
		for (int j = 0; j < tempTab.size() - 1; j++)
		{
			if (tempTab[j + 1].x < tempTab[j].x)
				swap(tempTab[j + 1], tempTab[j]);
		}
	}

	return getDistanceLinePoint(tempTab[0], tempTab[1], center);
}

double BaseFrame::getYCoord(Point2d center)
{
	vector<Point2f> tempTab = pointsTab;
	for (int i = 0; i < tempTab.size() - 1; i++)
	{
		for (int j = 0; j < tempTab.size() - 1; j++)
		{
			if (tempTab[j + 1].y > tempTab[j].y)
				swap(tempTab[j + 1], tempTab[j]);
		}
	}
	return getDistanceLinePoint(tempTab[0], tempTab[1], center);
}

double BaseFrame::getWidth()
{
	vector<Point2f> tempTab = pointsTab;

	for (int i = 0; i < tempTab.size() - 1; i++)
	{
		for (int j = 0; j < tempTab.size() - 1; j++)
		{
			if (tempTab[j + 1].y > tempTab[j].y)
				swap(tempTab[j + 1], tempTab[j]);
		}
	}
	return std::sqrt((tempTab[0].x - tempTab[1].x)*(tempTab[0].x - tempTab[1].x) + (tempTab[0].y - tempTab[1].y)*(tempTab[0].y - tempTab[1].y));
}

double BaseFrame::getHeight()
{
	vector<Point2f> tempTab = pointsTab;

	for (int i = 0; i < tempTab.size() - 1; i++)
	{
		for (int j = 0; j < tempTab.size() - 1; j++)
		{
			if (tempTab[j + 1].x < tempTab[j].x)
				swap(tempTab[j + 1], tempTab[j]);
		}
	}
	return std::sqrt((tempTab[0].x - tempTab[1].x)*(tempTab[0].x - tempTab[1].x) + (tempTab[0].y - tempTab[1].y)*(tempTab[0].y - tempTab[1].y));
}

double BaseFrame::getDistanceLinePoint(Point2f p1, Point2f p2, Point2f p3)
{
	double a = p2.y - p1.y;
	double b = p1.x - p2.x;
	double c = p1.y*p2.x - p2.y*p1.x;
	return std::abs(a*p3.x + b * p3.y + c) / std::sqrt(a*a + b * b);
}


