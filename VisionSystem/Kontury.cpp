#include "Kontury.h"




ContourCreator::ContourCreator()
{
}

ContourCreator::~ContourCreator()
{
}

void ContourCreator::drawContours(const Mat& src, Mat& dst)
{
	dst = Mat::zeros(src.size(), CV_8UC3);

	findContours(src);
	findRectangles(src);
	drawContoursToDst(dst);

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
	dst = Mat::zeros(src.size(), CV_8UC3);

	findRectangles(src);
	drawContoursToDst(dst);

	auto index = getFrameRectangleIndex(minRect, contours);	//indeks prostok¹ta ramki
	
	Point2f rect_points[4];	//punkty najwiekszego prostokata
	minRect[index].points(rect_points);

	shapesToDraw.push_back(RamkaPodloza(rect_points));
	drawShapes(dst);

}

void ContourCreator::drawCoordinateSystem(const Mat & src, Mat & dst)
{
	dst = Mat::zeros(src.size(), CV_8UC3);

	findRectangles(src);
	drawContoursToDst(dst);

	auto index = getFrameRectangleIndex(minRect, contours);	//indeks prostok¹ta ramki

	Point2f rect_points[4];	//punkty najwiekszego prostokata
	minRect[index].points(rect_points);

	shapesToDraw.push_back(RamkaPodloza(rect_points));
	drawShapes(dst);
}

void ContourCreator::findContours(const Mat& src)
{
	cv::findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
}

void ContourCreator::findRectangles(const Mat & src)
{
	if (contours.data() == nullptr)
	{
		findContours(src);
	}
	minRect.reserve(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(contours[i]);
	}
}

void ContourCreator::drawContoursToDst(Mat & dst)
{
	if (contours.data() == nullptr)
	{
		cout << "brak konturow" << endl;
		exit(1);
	}
		
	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::drawContours(dst, contours, (int)i, Scalar(0, 255, 0));
	}
}

void ContourCreator::drawShapes(Mat & dst)
{
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





