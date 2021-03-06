#include "Video.h"
#include "Contours.h"
#include "Calibration.h"
#include "Filter.h"
#include "MedianBlurFilter.h"
#include "BinaryThreshFilter.h"
#include "CannyFilter.h"
#include "GrayFilter.h"
#include <mutex>

using namespace cv;
using namespace std;


Video::Video(const std::string p_iPadress = "http://192.168.1.10:8080/video?x.mjpeg")
{
	createFiltersTab();
	m_videoCap.open(p_iPadress.c_str());
	checkIfOpened();
	m_jobList.push_back(&Video::source);
	m_jobList.push_back(&Video::processed);
}

void Video::calibrate()
{
	MedianBlurFilter l_mBlurFilter;
	BinaryThreshFilter l_binaryThreshFilter;
	CannyFilter l_cannyfilter;

	readFrame();
	l_mBlurFilter.filtr(m_currentFrame);
	m_calibrator.setSource(m_currentFrame);
	m_calibrator.startCalibrationThreshold();
	l_binaryThreshFilter.setBinaryThreshParam(m_calibrator.getThreshParam());
	l_binaryThreshFilter.filtr(m_currentFrame);
	m_calibrator.startCalibrationCanny();
	l_cannyfilter.setCannyParams(m_calibrator.getCannyParams());
}

void Video::processed()
{
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);
	applyFilters();
	imshow("MyVideo", m_outputFrame);
}

void Video::source()
{
	namedWindow("MySource", CV_WINDOW_AUTOSIZE);
	imshow("MySource", m_currentFrame);
}

void Video::addFilter(std::unique_ptr<Filter> p_filter)
{
	m_filTab.push_back(std::move(p_filter));
}

void Video::startStreaming(Coords& p_coords, std::mutex& p_mutex)
{
    do
    {
        readFrame();
        for(auto l_job : m_jobList)
        {
            (this->*l_job)();
        }
        if(m_currentCoords)
        {
            std::lock_guard<std::mutex> guard(p_mutex);
            p_coords = *m_currentCoords;
        }

    } while(!waitForKey(30, 27));
}

void Video::addJob(void (Video::*f)())
{
	m_jobList.push_back(f);
}

void Video::addJob(jobs newJob)
{
	switch (newJob)
	{
	case 0:
		addJob(&Video::source);
		break;
	case 1:
		addJob(&Video::processed);
		break;
	case 2:
		addJob(&Video::addContours);
		break;
	case 3:
		addJob(&Video::addFrame);
		break;
	case 4:
		addJob(&Video::addCoordinateSystem);
		break;
	case 5:
		addJob(&Video::addObjectOnFrame);
	}

}

void Video::clearJobs()
{
	m_jobList.clear();
}

void Video::addContours()
{
	namedWindow("contours", CV_WINDOW_AUTOSIZE);
	applyFilters();
	ContourCreator contours(m_outputFrame);
	Mat dst;
	contours.drawContoursOnly(dst);
	imshow("contours", dst);	
}

void Video::addFrame()
{
	namedWindow("frame", CV_WINDOW_AUTOSIZE);
	applyFilters();
	ContourCreator contours(m_outputFrame);
	contours.addFrame();
	contours.drawShapes(m_currentFrame);
	imshow("frame", m_currentFrame);
}

void Video::addCoordinateSystem()
{
	namedWindow("coordinateSystem", CV_WINDOW_AUTOSIZE);
	applyFilters();
	ContourCreator contours(m_outputFrame);
	contours.addCoordinateSystem();
	contours.drawShapes(m_currentFrame);
	imshow("coordinateSystem", m_currentFrame);
}

void Video::addObjectOnFrame()
{
	namedWindow("rectObj", CV_WINDOW_AUTOSIZE);
	applyFilters();
	ContourCreator contours(m_outputFrame);
	contours.addFrame();
	contours.addObject();

	m_currentCoords = contours.getAbsoluteObjectCoords(SHEET_WIDTH, SHEET_HEIGHT);
	checkCoords(0.8);
	contours.drawShapes(m_currentFrame);
	imshow("rectObj", m_currentFrame);
}

void Video::checkIfOpened()
{
	if (!m_videoCap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		exit(1);
	}
}

void Video::readFrame()
{
	bool bSuccess = m_videoCap.read(m_currentFrame); // read a new frame from video
	if (!bSuccess) //if not success, break loop
	{
		cout << "Cannot read a frame from video stream" << endl;
		exit(1);
	}
}

void Video::createFiltersTab()
{
	m_filTab.push_back(std::make_unique<GrayFilter>());
	m_filTab.push_back(std::make_unique<MedianBlurFilter>());
	m_filTab.push_back(std::make_unique<BinaryThreshFilter>());
	m_filTab.push_back(std::make_unique<CannyFilter>());
}

void Video::applyFilters()
{
	m_currentFrame.copyTo(m_outputFrame);
	for (auto& filter : m_filTab)
	{
		filter->filtr(m_outputFrame);
	}
}

bool Video::waitForKey(int ms, int key)
{
	if (waitKey(ms) == key) 
	{
		cout << "esc key is pressed by user" << endl;
		return true;
	}
	return false;
}

void Video::checkCoords(double scale)
{
    if (m_currentCoords)
    {
        if (m_currentCoords->first > scale*SHEET_WIDTH || m_currentCoords->first > scale*SHEET_HEIGHT)
        {
            m_currentCoords = std::nullopt;
        }
    }
}


