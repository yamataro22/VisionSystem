#pragma once
#include "Filter.h"

struct CannyParameters
{
public:
	int cannyThresh;
	int cannyMaxThresh = 100;
	int cannyRatio;
	int	cannyKernel;

	CannyParameters();
	CannyParameters(int, int, int);

	CannyParameters& operator=(const CannyParameters& p_cannyParams) = default;
	CannyParameters(const CannyParameters&) = default;
};


class CannyFilter : public Filter
{
public:

	CannyFilter();
	~CannyFilter();
	void filtr(Mat& src) override;
	void filtr(const Mat&, Mat&) override;
	void setCannyParams(CannyParameters);

private:

	CannyParameters m_cannyParams;

};

