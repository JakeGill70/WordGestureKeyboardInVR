#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class VideoStream
{
public:	
	int getVideoHeight();
	int getVideoWidth();
	Mat getFrame();
	Mat getFrameBuffer();
	Mat getThresh();
	vector<vector<Point>> getLargestBlob();
	int getCenterHistorySize();
	void setCenterHistorySize();
	void mirrorVideo();
	void blurVideo();
	void cvtColor();

private:
	VideoCapture cap;
	Mat frame;
	Mat frameBuffer;
	Mat thresh;

	int centerHistorySize;
	vector<Point> centerHistory;

	bool isMirroring;
};

