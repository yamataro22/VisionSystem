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
	auto index = getBiggestRectangleIndex(minRect, contours);
	Point2f rect_points[4];	//punkty najwiekszego prostokata
	minRect[index].points(rect_points);
	shapesToDraw.push_back(make_unique<RamkaPodloza>(rect_points));
}

void ContourCreator::addCoordinateSystem()
{
	findRectangles();
	auto index = getBiggestRectangleIndex(minRect, contours);	//indeks prostok¹ta ramki
	Point2f rect_points[4];	//punkty najwiekszego prostokata
	minRect[index].points(rect_points);
	shapesToDraw.push_back(make_unique<CoordinateSystem>(rect_points));
}

void ContourCreator::addObject()
{
	
	if (minRect.empty())
	{
		findRectangles();
	}
	sortByArea(minRect);
	auto frameIndex = getBiggestRectangleIndex(minRect, contours);
	eliminateDuplicates(minRect, frameIndex, 5);
	minRect.erase(minRect.begin() + frameIndex);

	Point2f rect_points[4];
	minRect[0].points(rect_points);
	objectToMove = make_unique<Ksztalt>(rect_points);
	shapesToDraw.push_back(objectToMove);
}

void ContourCreator::addAllRectangles()
{
	if (minRect.empty())
	{
		findRectangles();
	}
	eliminateDuplicates(minRect, getBiggestRectangleIndex(minRect, contours), 5);
	for (int i = 0; i < minRect.size(); i++)
	{
		Point2f rectPoints[4];
		minRect[i].points(rectPoints);
		shapesToDraw.push_back(make_unique<RamkaPodloza>(rectPoints));
	}
	cout << "Wykryto " << minRect.size() << "prostokatow" << endl;
}

void ContourCreator::drawContoursOnly(Mat& dst)
{
	dst = Mat::zeros(src.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::drawContours(dst, contours, (int)i, Scalar(0, 255, 0));
	}
}

double * ContourCreator::getObjectRecativeCoords(Point2f* framePoints)
{
	if (objectToMove == nullptr)
	{
		return nullptr;
	}
	else
	{
		double * pointArray = new double[2];
		ObiektProstokatny *obj = dynamic_cast<ObiektProstokatny*>(objectToMove.get());
		Point2f centerPoint = obj->getCenterPoint();

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
		minRect.push_back(minAreaRect(contours[i]));
	}
}

void ContourCreator::drawShapes(Mat& dst)
{
	if (dst.empty())
	{
		dst = Mat::zeros(src.size(), CV_8UC3);
	}
	for (int i = 0; i < shapesToDraw.size(); i++)
	{
		shapesToDraw[i]->drawShape(dst);
	}
}

int ContourCreator::getBiggestRectangleIndex(const vector<RotatedRect> &boundRect, const vector<vector<Point>>& contours)
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

void ContourCreator::sortByArea(vector<RotatedRect> rectangles)
{
	for (int i = 0; i < rectangles.size()-1; i++)
	{
		for (int j = 0; j < rectangles.size() - 1; j++)
		{
			if (rectangles[j + 1].size.area() > rectangles[j].size.area())
				swap(rectangles[j + 1], rectangles[j]);
		}
	}
}

void ContourCreator::eliminateDuplicates(vector<RotatedRect>& rectangles, int dupIndex, int percentError)
{
	auto frameArea = rectangles[dupIndex].size.area();
	auto max = frameArea + percentError * 0.01*frameArea;
	auto min = frameArea - percentError * 0.01*frameArea;
	for (int i = 0; i < rectangles.size(); i++)
	{
		if (i == dupIndex)
		{
			continue;
		}
		else
		{
			auto currentArea = rectangles[i].size.area();
			if ((currentArea > min) && (currentArea < max))
			{
				rectangles.erase(rectangles.begin() + i);
			}
		}
	}

}







