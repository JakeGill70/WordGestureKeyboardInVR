#pragma once
#ifndef VIRTUAL_KEY_H
#define VIRTUAL_KEY_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class VirtualKey
{
public:
	string letter;
	Rect transform;
	Scalar fontColor;
	Scalar buttonColor;
	VirtualKey();
	VirtualKey(string letter, Rect position);
	void drawKey(Mat inputOutputArray);
	void drawButton(Mat inputOutputArray);
	void drawLetter(Mat inputOutputArray);
};

#endif