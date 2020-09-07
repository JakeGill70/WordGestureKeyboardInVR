#pragma once
#ifndef FRAME_CONTROLLER_H
#define FRAME_CONTROLLER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ColorRange.h"

using namespace std;
using namespace cv;

class FrameController
{
public:
	FrameController();

	cv::Mat getFrameFromCamera();
	int getFrameHeight();
	int getFrameWidth();
	static void displayFrame(cv::Mat frame, string windowName);
	static void addCircleToFrame(cv::Mat frame, cv::Point position, cv::Scalar color);
	static void addWordToType(cv::Mat frame, string word);

private:
	cv::VideoCapture cap;
	int frameHeight;
	int frameWidth;
	cv::Mat lastFrameFromCamera;
};

#endif