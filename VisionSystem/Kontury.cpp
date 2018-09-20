#include "Kontury.h"




ContourCreator::ContourCreator(const Mat& src, Mat& dst)
{
}

ContourCreator::~ContourCreator()
{
}

void ContourCreator::drawContours(const Mat& src, Mat& dst)
{
	dst = Mat::zeros(src.size(), CV_8UC3);
	vector<vector<Point> > contours;
	cv::findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<RotatedRect> minRect(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(contours[i]);
	}

	auto index = getFrameRectangleIndex(minRect, contours);

	Scalar color = Scalar(0, 255, 0);

	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::drawContours(dst, contours, (int)i, color);
	}
}

void ContourCreator::addText(Mat& src, const char * text)
{
	int lineType = 8;
	Point org;
	int width = src.rows;
	int heigh = src.cols;

	org.x = 5 * width / 5;
	org.y = static_cast<int>(3.5 * heigh / 5);

	putText(src, text, org, FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2, lineType);
}

void ContourCreator::drawFrameRectangle(const Mat& src, Mat& dst)
{
	vector<vector<Point> > contours;
	cv::findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<RotatedRect> minRect(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(contours[i]);
	}

	auto index = getFrameRectangleIndex(minRect, contours);

	cout << "indeks: " << index << endl;
	Scalar color = Scalar(0, 255, 0);
	dst = Mat::zeros(src.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::drawContours(dst, contours, (int)i, color);
	}

	Point2f rect_points[4];
	

	minRect[index].points(rect_points);
	shapesToDraw.push_back(RamkaPodloza(rect_points));
	shapesToDraw.push_back(CoordinateSystem(rect_points));
	
	shapesToDraw[0].drawShape(dst);
}

int ContourCreator::getFrameRectangleIndex(const vector<RotatedRect> &boundRect, const vector<vector<Point>>& contours)
{
	int index = 0;
	for (int i = 0, max = 0; i < boundRect.size(); i++)
	{
		auto straightRect = boundRect[i].boundingRect();
		if (max < straightRect.area())
		{
			max = straightRect.area();
			index = i;
		}
	}
	return index;
}





