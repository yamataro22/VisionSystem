#include "SobelFilter.h"



SobelFilter::SobelFilter()
	:Filter(), m_params(CV_16S, 1, 0, 1)
{
}

SobelFilter::~SobelFilter()
{
}

void SobelFilter::filtr(Mat & p_src)
{
	Mat l_dst(p_src);
	Mat grad_x(p_src);
	Mat grad_y(p_src);

	Mat abs_grad_x, abs_grad_y;
	Sobel(p_src, grad_x, m_params.m_imageDepth, 1, 0, m_params.m_ksize, m_params.m_scale, m_params.m_delta, BORDER_DEFAULT);
	Sobel(p_src, grad_y, m_params.m_imageDepth, 0, 1, m_params.m_ksize, m_params.m_scale, m_params.m_delta, BORDER_DEFAULT);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, l_dst);
	l_dst.copyTo(p_src);
}

void SobelFilter::filtr(const Mat & p_src, Mat & p_dst)
{
	Mat grad_x(p_src);
	Mat grad_y(p_src);

	Mat abs_grad_x, abs_grad_y;
	Sobel(p_src, grad_x, m_params.m_imageDepth, 1, 0, m_params.m_ksize, m_params.m_scale, m_params.m_delta, BORDER_DEFAULT);
	Sobel(p_src, grad_y, m_params.m_imageDepth, 0, 1, m_params.m_ksize, m_params.m_scale, m_params.m_delta, BORDER_DEFAULT);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, p_dst);
}

void SobelFilter::setSobelParams(SobelParameters & p_newParams)
{
	m_params = p_newParams;
}

SobelParameters::SobelParameters(int p_ddep, int p_ksiz, int p_del, int p_sc)
	: m_imageDepth(p_ddep), m_ksize(p_ksiz), m_delta(p_del), m_scale(p_sc)
{
}
