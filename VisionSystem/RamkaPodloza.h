#pragma once
#include "Ksztalt.h"

class RamkaPodloza :
	public Ksztalt
{
public:
	RamkaPodloza(cv::Point2f ppintTab[]);
	~RamkaPodloza();
	void drawShape(cv::Mat& dst) override;
};

