#pragma once
#include "RamkaPodloza.h"
class ObiektProstokatny :
	public RamkaPodloza
{
public:
	ObiektProstokatny(cv::Point2f ppintTab[]);
	~ObiektProstokatny();
	Point2f getCenterPoint();
	void drawShape(cv::Mat& dst) override;

};

