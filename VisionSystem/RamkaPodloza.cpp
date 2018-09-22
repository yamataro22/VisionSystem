#include "RamkaPodloza.h"





RamkaPodloza::RamkaPodloza(cv::Point2f ppintTab[]) : Ksztalt(ppintTab)
{	
}

RamkaPodloza::~RamkaPodloza()
{
}

void RamkaPodloza::drawShape(cv::Mat & src)
{
	for (int j = 0; j < 4; j++)
	{
		line(src, pointsTab[j], pointsTab[(j + 1) % 4], Scalar(0, 255, 0));
	}
}
