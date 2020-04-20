#pragma once
#include "VirtualKey.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

VirtualKey::VirtualKey(string letter, Rect position) {
	this->letter = letter;
	this->position = position;
	this->fontColor = fontColor;
	this->buttonColor = Scalar(220, 220, 220);
	this->fontColor = Scalar(0);
}

void VirtualKey::drawKey(Mat inputOutputArray) {
	// Define Button
	// See Alexander Taubenkorb's answer for details
	// https://stackoverflow.com/questions/24480751/how-to-create-a-semi-transparent-shape
	// His implementation was inspired by this blog post
	// http://bistr-o-mathik.org/2012/06/13/simple-transparency-in-opencv/
	
	// Make a copy of the current frame
	Mat overlay;
	inputOutputArray.copyTo(overlay);
	
	// Draw Button
	drawButton(overlay);

	// Draw Letter
	drawLetter(overlay);

	// Draw Key
	double alpha = 0.50;
	addWeighted(overlay, alpha, inputOutputArray, 1 - alpha, 0, inputOutputArray);
}

void VirtualKey::drawButton(Mat inputOutputArray) {
	// Define Button
	Rect rect(this->position.x, this->position.y, this->position.width, this->position.height);
	Scalar buttonColor = this->buttonColor;
	
	// Draw button
	rectangle(inputOutputArray, rect, buttonColor, -1);
}

void VirtualKey::drawLetter(Mat inputOutputArray) {
	// Define Letter
	string textToDisplay = this->letter;
	Point keyCorner = Point(this->position.x, this->position.y);
	int fontStyle = cv::FONT_HERSHEY_SIMPLEX;
	int fontScaling = 1;
	Scalar fontColor = this->fontColor;
	int lineThickness = 3;
	int lineType = cv::LINE_4;

	// Translate the position of the letter such that it is in the center of a button
	keyCorner.y += fontScaling * 20 + 5;
	keyCorner.x += 5;
	
	// Draw Letter
	cv::putText(inputOutputArray, textToDisplay, keyCorner, fontStyle, fontScaling, fontColor, lineThickness, lineType);
}