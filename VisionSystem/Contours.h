#pragma once
#include "Defines.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <memory>
#include <optional>

using coordPair = std::pair<double, double>;
class Shape;
class CoordinateSystem;
class BaseFrame;


class ContourCreator
{
public:
	explicit ContourCreator(const cv::Mat&);

	void addFrame();
	void addCoordinateSystem();
	void addObject();
	void addAllRectangles();
	void addText(cv::Mat&, const char*);

	void drawShapes(cv::Mat&);
	void drawContoursOnly(cv::Mat&);
    std::optional<Coords> getRelativeObjectCoords();
    std::optional<Coords> getAbsoluteObjectCoords(double p_width, double p_height);

private:

	cv::Mat src;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::RotatedRect> minRect;
	std::vector<std::shared_ptr<Shape>> shapesToDraw;
	std::shared_ptr<Shape> detectedObject;
	std::shared_ptr<BaseFrame> mainFrame;
	cv::Point2f centerCoords;

	void findContours();
	void findRectangles();
	void updateCenterCoords();
	static int getBiggestRectangleIndex(const std::vector<cv::RotatedRect>&,
										const std::vector<std::vector<cv::Point>>&);
	void sortByArea(std::vector<cv::RotatedRect>);
	void eliminateDuplicates(std::vector<cv::RotatedRect>&, int, int);
    std::optional<Coords> getFrameScale(double, double);
};

