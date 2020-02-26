#pragma once
#include "ColorTracker.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


//using namespace std;
//using namespace cv;
//
//cv::Scalar minHSV;
//cv::Scalar maxHSV;
//cv::Scalar currentPositionColor;
//cv::Scalar averagePositionColor;
//vector<cv::Point> centerHistory;
//int centerHistorySize;
//cv::Point currentPosition;
//
//void update(cv::Mat image);
//cv::Point getUpdate(cv::Mat image);
//cv::Point getCurrentPosition(cv::Mat image);
//cv::Point getAveragePosition(cv::Mat image);
//
//private:
//	vector<vector<cv::Point>> findShapes(cv::Mat thresh);
//	vector<cv::Point> findBiggestShape(vector<vector<cv::Point>> contours);
//	cv::Point findCenterOfShape(vector<cv::Point> contour);
//	void drawCircle(cv::Mat image, cv::Point);
//	void shiftHistory();