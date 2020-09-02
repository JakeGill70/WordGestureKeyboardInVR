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
	VirtualKeyboard(Point startPosition, Point keySize, int numberOfLetters, char letters[], int rowOffsets[]);

	void drawKeyboard(cv::Mat* inputOutputArray);
	void setKeyColor(cv::Scalar c);
	void setFontColor(cv::Scalar c);
	void setKeySize(cv::Point size);
	VirtualKey getKey(int i);
	VirtualKey getKey(char letter);
private:
	int numberOfKeys;
	VirtualKey keys[50];
	//void initKeys(Point startPosition, Point keySize);
};

#endif