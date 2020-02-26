#pragma once
#ifndef COLOR_TRACKER_H
#define COLOR_TRACKER_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class ColorTracker
{
public:
	ColorTracker(cv::Scalar minHSV, cv::Scalar maxHSV);
	
	void update(cv::Mat image);
	cv::Point getUpdate(cv::Mat image);
	cv::Point getCurrentPosition();
	cv::Point getAveragePosition();
	void setMinHSV(cv::Scalar c);
	void setMaxHSV(cv::Scalar c);
	void setCurrentPositionColor(cv::Scalar c);
	void setAveragePositionColor(cv::Scalar c);

private:
	cv::Scalar minHSV;
	cv::Scalar maxHSV;
	cv::Scalar currentPositionColor;
	cv::Scalar averagePositionColor;
	cv::Point currentPosition;
	vector<cv::Point> centerHistory;
	int centerHistorySize;

	vector<vector<cv::Point>> findShapes(cv::Mat thresh);
	vector<cv::Point> findBiggestShape(vector<vector<cv::Point>> contours);
	cv::Point findCenterOfShape(vector<cv::Point> contour);
	void drawCircle(cv::Mat image, cv::Point);
	void shiftHistory();
};

#endif