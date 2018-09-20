#include "Ksztalt.h"


Ksztalt::Ksztalt(cv::Point2f points[])
{
	pointsOld = points;
	int n = sizeof(points) / sizeof(points[0]);
	for (int i = 0; i < 0; i++) 
	{
		pointsTab.push_back(points[i]);
	}
}

Ksztalt::~Ksztalt()
{
}
