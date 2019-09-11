#pragma once
#include "Filter.h"

struct SobelParameters {
	int m_imageDepth;
	int m_ksize;
	int m_delta;
	int m_scale;

	SobelParameters(int, int, int, int);
};


class SobelFilter : public Filter
{
public:
	SobelFilter();
	~SobelFilter();
	void filtr(Mat& src) override;
	void filtr(const Mat&, Mat&) override;
	void setSobelParams(SobelParameters&);

private:

	SobelParameters m_params;
};

