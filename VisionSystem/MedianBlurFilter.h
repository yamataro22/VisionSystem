#pragma once
#include "Filter.h"
class MedianBlurFilter : public Filter
{
public:
	MedianBlurFilter();
	void filtr(Mat& src) override;
	void filtr(const Mat& src, Mat& dst) override;
	void setmBlurParam(int);

private:
	int m_mBlurParam;
};

