#pragma once
#include "ColorTracker.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

ColorTracker::ColorTracker(Scalar minHSV, Scalar maxHSV) {
	this->setMinHSV(minHSV);
	this->setMaxHSV(maxHSV);
	this->setCurrentPositionColor(Scalar(255, 255, 255));
	this->setAveragePositionColor(Scalar(0, 255, 255));
	this->centerHistorySize = 3;
	this->centerHistory = vector<Point>(this->centerHistorySize);
}

void ColorTracker::setMinHSV(Scalar c) {
	this->minHSV = c;
}

void ColorTracker::setMaxHSV(Scalar c) {
	this->maxHSV = c;
}

void ColorTracker::setCurrentPositionColor(Scalar c) {
	this->currentPositionColor = c;
}

void ColorTracker::setAveragePositionColor(Scalar c) {
	this->currentPositionColor = c;
}

void ColorTracker::update(cv::Mat image) {
	
}

Point ColorTracker::getUpdate(cv::Mat image) {
	this->update(image);
	return this->getAveragePosition();
}

Point ColorTracker::getCurrentPosition() {

}

Point ColorTracker::getAveragePosition() {

}
//public:
//	ColorTracker(cv::Scalar minHSV, cv::Scalar maxHSV);
//
//	void update(cv::Mat image);
//	cv::Point getUpdate(cv::Mat image);
//	cv::Point getCurrentPosition();
//	cv::Point getAveragePosition();
//	void setMinHSV(cv::Scalar c);
//	void setMaxHSV(cv::Scalar c);
//	void setCurrentPositionColor(cv::Scalar c);
//	void setAveragePositionColor(cv::Scalar c);
//
//private:
//	cv::Scalar minHSV;
//	cv::Scalar maxHSV;
//	cv::Scalar currentPositionColor;
//	cv::Scalar averagePositionColor;
//	cv::Point currentPosition;
//	vector<cv::Point> centerHistory;
//	int centerHistorySize;
//
//	vector<vector<cv::Point>> findShapes(cv::Mat thresh);
//	vector<cv::Point> findBiggestShape(vector<vector<cv::Point>> contours);
//	cv::Point findCenterOfShape(vector<cv::Point> contour);
//	void drawCircle(cv::Mat image, cv::Point);
//	void shiftHistory();