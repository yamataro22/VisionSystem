#include "Shape.h"


Shape::Shape(cv::Point2f points[])
{
	for (int i = 0; i < 4; i++) 
	{
		pointsTab.push_back(points[i]);
	}
}

