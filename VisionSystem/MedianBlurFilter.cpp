#include "MedianBlurFilter.h"

MedianBlurFilter::MedianBlurFilter() : m_mBlurParam(9)
{
}

void MedianBlurFilter::filtr(Mat& src)
{
	medianBlur(src, src, m_mBlurParam);
}
void MedianBlurFilter::filtr(const Mat& src, Mat& dst)
{
	medianBlur(src, dst, m_mBlurParam);
}

void MedianBlurFilter::setmBlurParam(int p_newParam)
{
	m_mBlurParam = p_newParam;
}
