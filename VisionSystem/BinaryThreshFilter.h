#pragma once
#include "Filter.h"
class BinaryThreshFilter : public Filter
{
public:
	BinaryThreshFilter(int p_thresh = 140);
	~BinaryThreshFilter();

	void filtr(Mat& src) override;
	void filtr(const Mat& src, Mat& dst) override;
	void setBinaryThreshParam(int);

private:
	
	int m_binaryThresh;
	const int MAX_BINARY_THRESH = 255;
};

