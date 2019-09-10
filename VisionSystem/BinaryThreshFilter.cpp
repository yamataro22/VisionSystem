#include "BinaryThreshFilter.h"



BinaryThreshFilter::BinaryThreshFilter(int p_thresh)
	:Filter()
{
}

BinaryThreshFilter::~BinaryThreshFilter()
{
}

void BinaryThreshFilter::filtr(Mat & src)
{
	threshold(src, src, m_binaryThresh, MAX_BINARY_THRESH, 0);
}

void BinaryThreshFilter::filtr(const Mat & src, Mat & dst)
{
	threshold(src, dst, m_binaryThresh, 255, 0);
}

void BinaryThreshFilter::setBinaryThreshParam(int p_binaryThresh)
{
	m_binaryThresh = p_binaryThresh;
}