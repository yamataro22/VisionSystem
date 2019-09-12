#pragma once
#include "BaseFrame.h"

class RectangularShape :
	public BaseFrame
{
public:
	RectangularShape(cv::Point2f ppintTab[]);
	~RectangularShape();
	Point2f getCenterPoint() override;
	void drawShape(cv::Mat& dst) override;

};

