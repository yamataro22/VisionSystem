#pragma once
#include "Filter.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

struct RgbThreshParameters
{
	int low_r, low_g, low_b;
	int high_r, high_g, high_b;

	RgbThreshParameters(int, int, int, int, int, int);
	RgbThreshParameters();
	Scalar getLowRgbScalar();
    Scalar getHighRgbScalar();
};


class RgbThreshFilter : public Filter
{
public:

	void filtr(Mat& src) override;
	void filtr(const Mat& src, Mat& dst) override;
	void setRgbThreshParams(int, int, int, int, int, int);
	void setRgbThreshParams(RgbThreshParameters);

private:

	RgbThreshParameters m_rgbThreshParams;

};

