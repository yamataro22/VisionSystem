#include "Kontury.h"




ContourCreator::ContourCreator(const Mat& s):src(s)
{
	findContours();
}

ContourCreator::~ContourCreator()
{
}

void ContourCreator::addFrame()
{
	findRectangles();
	auto index = getFrameRectangleIndex(minRect, contours);
	Point2f rect_points[4];	//punkty najwiekszego prostokata
	minRect[index].points(rect_points);
	shapesToDraw.push_back(RamkaPodloza(rect_points));
}

void ContourCreator::addCoordinateSystem()
{
	findRectangles();
	auto index = getFrameRectangleIndex(minRect, contours);	//indeks prostok¹ta ramki
	Point2f rect_points[4];	//punkty najwiekszego prostokata
	minRect[index].points(rect_points);
	shapesToDraw.push_back(CoordinateSystem(rect_points));
}

void ContourCreator::drawContoursOnly(Mat& dst)
{
	dst = Mat::zeros(src.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::drawContours(dst, contours, (int)i, Scalar(0, 255, 0));
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


void ContourCreator::findContours()
{
	cv::findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
}

void ContourCreator::findRectangles()
{
	if (contours.data() == nullptr)
	{
		findContours();
	}
	minRect.reserve(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(contours[i]);
	}
}

void ContourCreator::drawShapes(Mat& dst)
{
	dst = Mat::zeros(src.size(), CV_8UC3);
	for (int i = 0; i < shapesToDraw.size(); i++)
	{
		shapesToDraw[i].drawShape(dst);
	}
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





