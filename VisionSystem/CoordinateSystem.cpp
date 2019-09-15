#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem(cv::Point2f pointTab[]) : Shape(pointTab)
{

}

void CoordinateSystem::drawShape(cv::Mat & dst)
{
    setLowestPointToTheEndOfPointTab();

	line(dst, pointsTab[3], pointsTab[2], Scalar(255, 0, 0), 9);
	line(dst, pointsTab[3], pointsTab[1], Scalar(255, 0, 0), 9);
}

void CoordinateSystem::sortPoints()
{
	int n = 4;

	for (int j = 0; j < n; j++)			//sortowanie malej�ce po Y
	{
		for (int i = n - 1; i > 0; i--)
		{
			if (pointsTab[i].y > pointsTab[i - 1].y)
			{
				swap(pointsTab[i], pointsTab[i - 1]);
			}
		}
	}

	if (pointsTab[3].x < pointsTab[2].x)
	{
		swap(pointsTab[3], pointsTab[2]);
		swap(pointsTab[0], pointsTab[1]);
	}
}

void CoordinateSystem::showPoints()
{
	for (int i = 0; i < 4; i++)
	{
		cout << "P" << i << ": x:" << pointsTab[i].x << "; y:" << pointsTab[i].y << endl;
	}
}

void CoordinateSystem::drawCoordinateSystem(Mat& currentMat, Point2f tab[])
{
	//TODO
}

void CoordinateSystem::setLowestPointToTheEndOfPointTab()
{
	sortPoints();
	double leftSide = norm(pointsTab[3] - pointsTab[1]);
	double rightSide = norm(pointsTab[3] - pointsTab[2]);
	if (rightSide > leftSide)	//case when middle point is not the lowest one
	{
		if (pointsTab[1].y > pointsTab[2].y)
			swap(pointsTab[1], pointsTab[2]);
		swap(pointsTab[2], pointsTab[3]);
		swap(pointsTab[0], pointsTab[1]);
	}
}
