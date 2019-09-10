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

/*
void Filter::filtr(Mat& src)
{
	switch (which)
	{
	case 0:
		gray(src);
		break;
	case 1:
		mBlur(src);
		break;
	case 2:
		thresh(src);
		break;
	case 3:
		gBlur(src);
		break;
	case 4:
		sharp(src);
		break;
	case 5:
		threshColor(src);
		break;
	case 6:
		canny(src);
		break;
	default:
		cout << "Nie wybrano porawnego filtru" << endl;
	}
}

void Filter::filtr(Mat & src, Mat & dst)
{
	switch (which)
	{
	case 0:
		gray(src, dst);
		break;
	case 1:
		mBlur(src, dst);
		break;
	case 2:
		thresh(src, dst);
		break;
	case 3:
		gBlur(src, dst);
		break;
	case 4:
		sharp(src, dst);
		break;
	case 5:
		threshColor(src, dst);
	case 6:
		canny(src, dst);
		break;
	default:
		cout << "Nie wybrano porawnego filtru" << endl;
	}
}
*/


void Filter::sobel(Mat & src, Mat & dst)
{
	Mat grad_x(src);
	Mat grad_y(src);
	
	Mat abs_grad_x, abs_grad_y;
	sobelParams parametry(CV_16S, 1, 0, 1);
	Sobel(src, grad_x, parametry.ddepth, 1, 0, parametry.ksize, parametry.scale, parametry.delta, BORDER_DEFAULT);
	Sobel(src, grad_y, parametry.ddepth, 0, 1, parametry.ksize, parametry.scale, parametry.delta, BORDER_DEFAULT);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
}

void Filter::sobel(Mat & src, Mat & dst, sobelParams parametry)
{
	Mat grad_x;
	Mat grad_y;
	Mat abs_grad_x, abs_grad_y;
	Sobel(src, grad_x, parametry.ddepth, 1, 0, parametry.ksize, parametry.scale, parametry.delta, BORDER_DEFAULT);
	Sobel(src, grad_y, parametry.ddepth, 0, 1, parametry.ksize, parametry.scale, parametry.delta, BORDER_DEFAULT);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
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

sobelParams::sobelParams(int ddep, int ksiz, int del, int sc): ddepth(ddep), ksize(ksiz), delta(del), scale(sc)
{

}


