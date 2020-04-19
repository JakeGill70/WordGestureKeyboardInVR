#pragma once
#ifndef COLOR_TRACKER_H
#define COLOR_TRACKER_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ColorRange.h"


using namespace std;
using namespace cv;

class ColorTracker
{
public:
	ColorTracker(ColorRange red, ColorRange white);
	
	void update(cv::Mat image);
	cv::Point getCurrentPosition();
	cv::Point getAveragePosition();
	void setRedColorRange(ColorRange c);
	void setWhiteColorRange(ColorRange c);
	ColorRange getRedColorRange();
	ColorRange getWhiteColorRange();
	cv::Mat getRedMask();
	cv::Mat getWhiteMask();

private:
	ColorRange red;
	ColorRange white;
	cv::Scalar currentPositionColor;
	cv::Scalar averagePositionColor;
	cv::Point currentPosition;
	vector<cv::Point> centerHistory;
	int centerHistorySize;
	cv::Mat redMask;
	cv::Mat whiteMask;

	vector<vector<cv::Point>> findShapes(cv::Mat mask);
	vector<cv::Point> findBiggestShape(cv::Mat mask);
	cv::Point findCenterOfShape(vector<cv::Point> contour);
	int findDistanceBetweenTwoPoints(cv::Point a, cv::Point b);
	void pushOntoPositionHistory(cv::Point p);
};

#endif