#include "Ksztalt.h"


Ksztalt::Ksztalt(cv::Point2f points[])
{
	pointsOld = points;
	for (int i = 0; i < 4; i++) 
	{
		pointsTab.push_back(points[i]);
	}
}

Ksztalt::~Ksztalt()
{
}
