#include "RgbThreshFilter.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

RgbThreshParameters::RgbThreshParameters() 
	: low_r(30), low_g(30), low_b(30), high_r(100), high_g(100), high_b(100)
{
}

RgbThreshParameters::RgbThreshParameters(int p_lowr, int p_lowg, int p_lowb, 
										 int p_highr, int p_highg, int p_highb)
	:low_r(p_lowr), low_g(p_lowg), low_b(p_lowb), high_g(p_highg), high_b(p_highb)
{
}

Scalar RgbThreshParameters::getLowRgbScalar() {
    return Scalar(low_b, low_g, low_r);
}

Scalar RgbThreshParameters::getHighRgbScalar() {
    return Scalar(high_b, high_g, high_r);;
}

RgbThreshFilter::RgbThreshFilter()
{
}


RgbThreshFilter::~RgbThreshFilter()
{
}

void RgbThreshFilter::filtr(Mat& p_src)
{
	inRange(p_src, cv::Scalar(m_rgbThreshParams.low_b, m_rgbThreshParams.low_g, m_rgbThreshParams.low_r)
		   ,cv::Scalar(m_rgbThreshParams.high_b, m_rgbThreshParams.high_g, m_rgbThreshParams.high_r), p_src);
}

void RgbThreshFilter::filtr(const Mat& p_src, Mat& p_dst)
{
	inRange(p_src, cv::Scalar(m_rgbThreshParams.low_b, m_rgbThreshParams.low_g, m_rgbThreshParams.low_r)
		   ,cv::Scalar(m_rgbThreshParams.high_b, m_rgbThreshParams.high_g, m_rgbThreshParams.high_r), p_dst);
}

void RgbThreshFilter::setRgbThreshParams(int lowr, int lowg, int lowb, int highr, int highg, int highb)
{
	m_rgbThreshParams = RgbThreshParameters(lowr, lowg, lowb, highr, highg, highb);
}

void RgbThreshFilter::setRgbThreshParams(RgbThreshParameters p_newParams)
{
	m_rgbThreshParams = p_newParams;
}