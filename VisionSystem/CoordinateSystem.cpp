#include "CoordinateSystem.h"




CoordinateSystem::CoordinateSystem(cv::Point2f pointTab[]) : Shape(pointTab)
{

}

CoordinateSystem::~CoordinateSystem()
{
}

void CoordinateSystem::drawShape(cv::Mat & dst)
{
	giveCoordPoints(pointsOld);

	line(dst, pointsOld[3], pointsOld[2], Scalar(255, 0, 0), 9);
	line(dst, pointsOld[3], pointsOld[1], Scalar(255, 0, 0), 9);
}

void CoordinateSystem::sortPoints(Point2f points[])
{
	int n = 4;

	for (int j = 0; j < n; j++)			//sortowanie malej¹ce po Y
	{
		for (int i = n - 1; i > 0; i--)
		{
			if (points[i].y > points[i - 1].y)
			{
				swap(points[i], points[i - 1]);
			}
		}
	}

	if (points[3].x < points[2].x)
	{
		swap(points[3], points[2]);
		swap(points[0], points[1]);
	}
}

void CoordinateSystem::showPoints(Point2f p[])
{
	for (int i = 0; i < 4; i++)
	{
		cout << "P" << i << ": x:" << p[i].x << "; y:" << p[i].y << endl;
	}
}

void CoordinateSystem::drawCoordinateSystem(Mat& currentMat, Point2f tab[])
{
	
}

void CoordinateSystem::giveCoordPoints(Point2f points[])
{
	sortPoints(points);
	double leftSide = norm(points[3] - points[1]);
	double rightSide = norm(points[3] - points[2]);
	if (rightSide > leftSide)	//sytuacja gdy punkt œrodkowy nie jest najni¿szy
	{
		if (points[1].y > points[2].y)
			swap(points[1], points[2]);
		swap(points[2], points[3]);
		swap(points[0], points[1]);
	}
	//funkcja zwraca pkt centralny uk³. wspó³ jako ostatni element talbicy
}
