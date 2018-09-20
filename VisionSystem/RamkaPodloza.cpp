#include "RamkaPodloza.h"





RamkaPodloza::RamkaPodloza(cv::Point2f ppintTab[]) : Ksztalt(ppintTab)
{
	if (pointsTab.size() != 4)
	{
		cout << "Prostokat musi miec 4 boki" << endl;;
		exit(1);
	}
		
}

RamkaPodloza::~RamkaPodloza()
{
}

void RamkaPodloza::drawShape(cv::Mat & src)
{
	cv::Scalar color = cv::Scalar(0, 255, 0);
	Mat dst = cv::Mat::zeros(src.size(), CV_8UC3);

	for (int j = 0; j < 4; j++)
	{
		line(src, pointsTab[j], pointsTab[(j + 1) % 4], color);
	}
}
