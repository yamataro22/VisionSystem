#include "Contours.h"
#include "Shape.h"
#include "BaseFrame.h"
#include "CoordinateSystem.h"
#include "RectangularShape.h"
#include <optional>
#include <algorithm>

using namespace cv;
using namespace std;

ContourCreator::ContourCreator(const Mat& s):src(s)
{
	findContours();
}

void ContourCreator::addFrame()
{
    findRectangles();

	if(!minRect.empty())
	{
		auto index = getBiggestRectangleIndex(minRect, contours);
		Point2f rect_points[4];	//biggest rectangle points
		minRect[index].points(rect_points);
        mainFrame = std::make_shared<BaseFrame>(rect_points);
		shapesToDraw.push_back(mainFrame);
	}
}
void ContourCreator::addCoordinateSystem()
{
	findRectangles();
	auto index = getBiggestRectangleIndex(minRect, contours);	//base rectangular index
	Point2f rect_points[4];
	minRect[index].points(rect_points);
	shapesToDraw.push_back(std::make_unique<CoordinateSystem>(rect_points));
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
			detectedObject = std::make_shared<RectangularShape>(rect_points);
			updateCenterCoords();
			shapesToDraw.push_back(detectedObject);
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
	for(auto& l_minRect : minRect)
    {
        Point2f rectPoints[4];
        l_minRect.points(rectPoints);
        shapesToDraw.push_back(std::make_unique<BaseFrame>(rectPoints));
    }
	cout << "Detected " << minRect.size() << " rectangles" << endl;
}

void ContourCreator::drawContoursOnly(Mat& dst)
{
	dst = Mat::zeros(src.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++)
	{
		cv::drawContours(dst, contours, (int)i, Scalar(0, 255, 0));
	}
}

std::optional<Coords> ContourCreator::getRelativeObjectCoords()
{
	if(detectedObject)
	{
        return std::make_pair(mainFrame->getXCoord(centerCoords), mainFrame->getYCoord(centerCoords));
	}
	else
	{
        return std::nullopt;
	}
}

std::optional<Coords> ContourCreator::getAbsoluteObjectCoords(double p_width, double p_height)
{
	
	auto l_scaledCoords = getFrameScale(p_width, p_height);
	auto l_relCoords = getRelativeObjectCoords();

	if (!(l_relCoords || l_scaledCoords))
	{
		return std::nullopt;
	}
	else
    {
        return std::make_pair(l_relCoords->first * l_scaledCoords->first, l_relCoords->second * l_scaledCoords->second);
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
	if (contours.size() == 0) return;

    minRect.reserve(contours.size());

    for(auto& l_contour : contours)
    {
        minRect.push_back(minAreaRect(l_contour));
    }
}

void ContourCreator::updateCenterCoords()
{
	if (detectedObject)
	{
        centerCoords = detectedObject->getCenterPoint();
	}
	else
	{
        cout << "Add coordinates firstly" << endl;
        exit(1);
	}
}

void ContourCreator::drawShapes(Mat& dst)
{
	if (dst.empty())
	{
		dst = Mat::zeros(src.size(), CV_8UC3);
	}
	for(const auto& shape: shapesToDraw)
    {
        shape->drawShape(dst);
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
    auto compFuntion = [](const RotatedRect& a, const RotatedRect& b){ return b.size.area() > a.size.area(); };
    std::sort(rectangles.begin(),rectangles.end(), compFuntion);
}

void ContourCreator::eliminateDuplicates(vector<RotatedRect>& rectangles, int dupIndex, int percentError)
{
	auto frameArea = rectangles[dupIndex].size.area();
	auto max = frameArea + percentError * 0.01*frameArea;
	auto min = frameArea - percentError * 0.01*frameArea;

    for (int i = 0; i < rectangles.size(); i++)
    {
        if (i != dupIndex)
        {
            auto currentArea = rectangles[i].size.area();

            if ((currentArea > min) && (currentArea < max))
            {
                rectangles.erase(rectangles.begin() + i);
            }
        }
    }
}

std::optional<Coords> ContourCreator::getFrameScale(double width, double height)
{
    if (shapesToDraw.empty())
    {
	    return std::nullopt;
    }
    else
    {
		return std::make_pair(width / mainFrame->getWidth(), height / mainFrame->getHeight());
	}
}







