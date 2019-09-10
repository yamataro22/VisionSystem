#pragma once
#include "Filter.h"

class GrayFilter : public Filter
{
public:
	GrayFilter();
	~GrayFilter();

	void filtr(Mat& src) override;
	void filtr(const Mat& src, Mat& dst) override;
};

