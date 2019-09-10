#include "GrayFilter.h"



GrayFilter::GrayFilter()
{
}


GrayFilter::~GrayFilter()
{
}

void GrayFilter::filtr(Mat & src)
{
	cvtColor(src, src, COLOR_BGR2GRAY);
}

void GrayFilter::filtr(const Mat & src, Mat & dst)
{
	int type = src.type();
	if (type == 0)
		return;
	cvtColor(src, dst, COLOR_BGR2GRAY);
}