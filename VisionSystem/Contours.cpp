#include "Contours.h"
#include "Shape.h"
#include "BaseFrame.h"
#include "CoordinateSystem.h"
#include "RectangularShape.h"

using namespace cv;
using namespace std;

ContourCreator::ContourCreator(const Mat& s):src(s)
{
	findContours();
}

ContourCreator::~ContourCreator()
{
	delete objToDraw;
}

void ContourCreator::addFrame()
{
	if (findRectangles() != nullptr)
	{
		auto index = getBiggestRectangleIndex(minRect, contours);
		Point2f rect_points[4];	//biggest rectangle points
		minRect[index].points(rect_points);
		shapesToDraw.push_back(new BaseFrame(rect_points));
	}

}

void ContourCreator::addCoordinateSystem()
{
	findRectangles();
	auto index = getBiggestRectangleIndex(minRect, contours);	//base rectangular index
	Point2f rect_points[4];
	minRect[index].points(rect_points);
	shapesToDraw.push_back(new CoordinateSystem(rect_points));
}

void ContourCreator::addObject()
{
	if (minRect.size() != 0)
	{
		sortByArea(minRect);
		auto frameIndex = getBiggestRectangleIndex(minRect, contours);
		eliminateDuplicates(minRect, frameIndex, 5);
		frameIndex = getBiggestRectangleIndex(minRect, contours);
		if (minRect.size() > 0)
		{
			minRect.erase(minRect.begin() + frameIndex);
		}


		Point2f rect_points[4];
		if (minRect.size() > 0)
		{
			minRect[0].points(rect_points);
			objToDraw = new RectangularShape(rect_points);
			updateCenterCoords(rect_points);
			shapesToDraw.push_back(objToDraw);
		}
	}
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
		shapesToDraw.push_back(new BaseFrame(rectPoints));
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

std::unique_ptr<coordPair> ContourCreator::getRelativeObjectCoords()
{
	if(objToDraw == nullptr)
	{
		return nullptr;
	}
	else
	{
		coordPair l_coordTab;
		BaseFrame * frame = dynamic_cast<BaseFrame*>(shapesToDraw[0]);
		l_coordTab.first = frame->getXCoord(centerCoords);
		l_coordTab.second = frame->getYCoord(centerCoords);

		return std::make_unique<coordPair>(l_coordTab);
	}
}

std::unique_ptr<coordPair>  ContourCreator::getAbsoluteObjectCoords(double p_width, double p_height)
{
	
	auto l_scaledCoords = getFrameScale(p_width, p_height);
	coordPair l_realCoords;
	auto l_relCoords = getRelativeObjectCoords();
	if (l_relCoords == nullptr || l_scaledCoords == nullptr)
	{
		return nullptr;
	}
	l_realCoords.first = l_relCoords->first * l_scaledCoords->first;
	l_realCoords.second = l_relCoords->second * l_scaledCoords->second;
	return std::make_unique<coordPair>(l_realCoords);
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

void* ContourCreator::findRectangles()
{
	if (contours.size() == 0)
	{
		return nullptr;
	}
	else
	{
		minRect.reserve(contours.size());
		for (size_t i = 0; i < contours.size(); i++)
		{
			minRect.push_back(minAreaRect(contours[i]));
		}
	}
	
}

void ContourCreator::updateCenterCoords(Point2f * framePoints)
{
	if (objToDraw == nullptr)
	{
		cout << "Add coordinates firstly" << endl;
		exit(1);
	}
	else
	{
		RectangularShape *rect = static_cast<RectangularShape*>(objToDraw);
		centerCoords = rect->getCenterPoint();
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

std::unique_ptr<coordPair> ContourCreator::getFrameScale(double width, double height)
{
	if (shapesToDraw.size() != 0)
	{
		coordPair l_scaleTab;
		BaseFrame * frame = dynamic_cast<BaseFrame*>(shapesToDraw[0]);
		l_scaleTab.first = width / frame->getWidth();
		l_scaleTab.second = height / frame->getHeight();

		return std::make_unique<coordPair>(l_scaleTab);
	}
	else
	{
		return nullptr;
	}
}







