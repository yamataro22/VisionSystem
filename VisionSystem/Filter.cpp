#include "Filter.h"



Filter::Filter():gBlurMSize(3)
{

}


Filter::~Filter()
{
}

void Filter::determineType(Mat & src)
{
	int type = src.type();
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	cout << "Typ maty: " << r << endl;
}

void Filter::setgBlurParam(int newParam)
{
	gBlurMSize = newParam;
}

void Filter::gBlur(Mat & src)
{
	GaussianBlur(src, src, Size(gBlurMSize, gBlurMSize), 0, 0, BORDER_DEFAULT);
}

void Filter::gBlur(const Mat & src, Mat & dst)
{
	GaussianBlur(src, dst, Size(gBlurMSize, gBlurMSize), 0, 0, BORDER_DEFAULT);
}

void Filter::sharp(Mat & src)
{
	CV_Assert(src.depth() == CV_8U);
	Mat dst;
	dst.create(src.size(), src.type());
	const int channels = src.channels();

	for (int j = 1; j < src.rows - 1; ++j)
	{
		const uchar * previous = src.ptr<uchar>(j - 1);
		const uchar * current = src.ptr<uchar>(j);
		const uchar * next = src.ptr<uchar>(j + 1);

		uchar* output = dst.ptr<uchar>(j);

		for (int i = channels; i < channels * (src.cols - 1); ++i)
		{
			*output++ = saturate_cast<uchar>(5 * current[i]
				- current[i - channels] - current[i + channels] - previous[i] - next[i]);
		}
	}
	dst.copyTo(src);
}

void Filter::sharp(const Mat & src, Mat & dst)
{
	CV_Assert(src.depth() == CV_8U);

	dst.create(src.size(), src.type());
	const int channels = src.channels();

	for (int j = 1; j < src.rows - 1; ++j)
	{
		const uchar * previous = src.ptr<uchar>(j - 1);
		const uchar * current = src.ptr<uchar>(j);
		const uchar * next = src.ptr<uchar>(j + 1);

		uchar* output = dst.ptr<uchar>(j);

		for (int i = channels; i < channels * (src.cols - 1); ++i)
		{
			*output++ = saturate_cast<uchar>(5 * current[i]
				- current[i - channels] - current[i + channels] - previous[i] - next[i]);
		}
	}
}

