#include "CannyFilter.h"


CannyParameters::CannyParameters() : cannyThresh(50), cannyRatio(3), cannyKernel(3)
{
}
CannyParameters::CannyParameters(int p_cParam, int p_cRatio, int p_cKernel) : cannyThresh(p_cParam), cannyRatio(p_cRatio), cannyKernel(p_cKernel)
{
}

CannyFilter::CannyFilter()
{
}

CannyFilter::~CannyFilter()
{
}

void CannyFilter::filtr(Mat& p_src)
{
	Canny(p_src, p_src, m_cannyParams.cannyThresh, m_cannyParams.cannyThresh*m_cannyParams.cannyRatio, m_cannyParams.cannyKernel);
}
void CannyFilter::filtr(const Mat& p_src, Mat& p_dst)
{
	Canny(p_src, p_dst, m_cannyParams.cannyThresh, m_cannyParams.cannyThresh*m_cannyParams.cannyRatio, m_cannyParams.cannyKernel);
}

void CannyFilter::setCannyParams(CannyParameters p_newParams)
{
	m_cannyParams = p_newParams;
}


