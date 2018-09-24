#include "ObiektProstokatny.h"



ObiektProstokatny::ObiektProstokatny(cv::Point2f ppintTab[]) : RamkaPodloza(ppintTab)
{
}


ObiektProstokatny::~ObiektProstokatny()
{
}

Point2f ObiektProstokatny::getCenterPoint()
{
	float xPos = (pointsTab[0].x + pointsTab[1].x + pointsTab[2].x + pointsTab[3].x)/4;
	float yPos = (pointsTab[0].y + pointsTab[1].y + pointsTab[2].y + pointsTab[3].y) / 4;

	return Point2f(xPos, yPos);
}

void ObiektProstokatny::drawShape(cv::Mat & dst)
{
	for (int j = 0; j < 4; j++)
	{
		line(dst, pointsTab[j], pointsTab[(j + 1) % 4], Scalar(255, 0, 0),5);
	}
	cv::circle(dst, getCenterPoint(), 5, Scalar(255, 0, 0), 10);
}
