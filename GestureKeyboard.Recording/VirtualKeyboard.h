#pragma once
#ifndef V_KBD_H
#define V_KBD_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "VirtualKey.h"

using namespace std;
using namespace cv;

class VirtualKeyboard
{
public:
	VirtualKeyboard(cv::Point position, cv::Point size, int rowOffsets[]);

	void drawKeyboard(cv::Mat inputOutputArray);
	void setKeyColor(Scalar c);
	void setFontColor(Scalar c);
	void setRowOffsets(int rowOffsets[]);
	VirtualKey getKey(int i);
	VirtualKey getKey(string letter);
private:
	VirtualKey keys[];
	void initKeys();
};

#endif