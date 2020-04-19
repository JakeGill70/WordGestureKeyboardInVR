#pragma once
#include "ColorTracker.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <limits.h>


using namespace std;
using namespace cv;

ColorTracker::ColorTracker(ColorRange red, ColorRange white) {
	this->setRedColorRange(red);
	this->setWhiteColorRange(white);
	this->centerHistory = vector<Point>(3);
}

void ColorTracker::setRedColorRange(ColorRange c) {
	this->red = c;
}

void ColorTracker::setWhiteColorRange(ColorRange c) {
	this->white = c;
}

void ColorTracker::update(cv::Mat image) {
	// Create an image buffer to manipulate
	// without affecting the parameter image
	Mat imageBuffer = Mat::zeros(image.rows, image.cols, CV_8UC3);

	// Copy the content of the image into the image buffer.
	// Smooth the image while maintaining sharp edges,
	//	so that simple shapes appear more "blob-ish"
	// Other parameters are from trial and error
	bilateralFilter(image, imageBuffer, 5, 50, 25);

	// Convert to HSV color space for better color referencing
	cvtColor(imageBuffer, imageBuffer, COLOR_BGR2HSV);

	// Create masks for the different color ranges
	redMask = Mat::zeros(image.rows, image.cols, CV_8UC3);
	whiteMask = Mat::zeros(image.rows, image.cols, CV_8UC3);

	// Create a mask of where a range of colors appear (Shades of red in HSV color space)
	inRange(imageBuffer, red.getMin(), red.getMax(), redMask);
	inRange(imageBuffer, white.getMin(), white.getMax(), whiteMask);

	// Find the biggest red shape
	vector<Point> biggestRed = findBiggestShape(redMask);

	// Find the center of the biggest red shape
	Point centerOfBiggestRed = findCenterOfShape(biggestRed);
	
	// Find all of the white shapes
	vector<vector<Point>> whiteShapes = findShapes(whiteMask);

	// Find the white spot closest to the center of the biggest red shape
	// Then let that point be the currentPosition of the light pen.
	currentPosition = Point(0, 0);
	int bestDistance = INT_MAX;
	for (int i = 0; i < whiteShapes.size(); i++)
	{
		Point centerOfWhiteShape = findCenterOfShape(whiteShapes[i]);
		int distance = findDistanceBetweenTwoPoints(centerOfWhiteShape, centerOfBiggestRed);
		if (distance < bestDistance) {
			bestDistance = distance;
			currentPosition = centerOfWhiteShape;
		}
	}

	// Update the position history to include the current position;
	pushOntoPositionHistory(currentPosition);
}

int ColorTracker::findDistanceBetweenTwoPoints(Point a, Point b) {
	// TODO: This should really be associated with the Point class, rather than the ColorTracker class
	// Explaination: starting at the square root is the normal formula for getting the 
	//		distance between two points. The round function will round it to the nearest
	//		whole number. After rounding, it is cast to an integer.
	return (int)round(sqrt(((a.x - b.x) * (a.x - b.x))));
}

vector<Point> ColorTracker::findBiggestShape(Mat mask) {
	// Create a pointer to the biggest shape (contour) found so far
	vector<Point>* biggestShape;

	// Default to the biggest shape
	// Create a new shape out of a single point
	// Centered a screen coords (0,0)
	vector<Point>* emptyShape = new vector<Point>();
	(*emptyShape).push_back(Point(0, 0));
	biggestShape = emptyShape;
	
	// Get a list of all outlines of each of the different shapes within the red mask
	vector<vector<Point>> shapes = findShapes(mask);
	
	if (!shapes.empty()) {
		// If the masks contains any shapes

		// Find the biggest shape (contour)
		int maxArea = 0;
		for (int i = 0; i < shapes.size(); i++)
		{
			int currentArea = contourArea(shapes[i]);
			if (currentArea > maxArea) {
				maxArea = currentArea;
				biggestShape = &shapes[i];
			}
		}
	}

	// Return the biggest shape
	return (*biggestShape);
	
}

Point ColorTracker::findCenterOfShape(vector<Point> contour) {
	// TODO: Figure out how this works and explain it
	Moments M = cv::moments(contour); 
	// Default the center of the object to screen coords (0,0)
	Point center(0, 0);
	// Protect against divde by 0 errors
	if (M.m00 != 0) { 
		center = Point((int)(M.m10 / M.m00), (int)(M.m01 / M.m00));
	}
	return center;
}

vector<vector<Point>> ColorTracker::findShapes(Mat mask) {
	vector<vector<Point>> contours;
	findContours(mask, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
	return contours;
}


Point ColorTracker::getCurrentPosition() {
	return this->currentPosition;
}

Point ColorTracker::getAveragePosition() {
	// Find the average center based on the history of current positions
	Point average(0, 0);
	// Sum
	for (int i = 0; i < centerHistory.size(); i++) {
		average.x += centerHistory[i].x;
		average.y += centerHistory[i].y;
	}
	// Divide by size
	average.x = average.x / centerHistory.size();
	average.y = average.y / centerHistory.size();
	
	// Return the average position
	return average;
}

Point ColorTracker::getBiasedPosition() {
	// Find the average center based on the history of current positions
	// Where newer values have a heavier weight than older values
	Point average(0, 0);
	// Sum
	double totalWeight = 0.0;
	double currentWeight = 0.0;
	for (int i = 0; i < centerHistory.size(); i++) {
		currentWeight = 1.0 / pow(2.0, (double)i);
		totalWeight += currentWeight;
		average.x += (int)(centerHistory[i].x * currentWeight);
		average.y += centerHistory[i].y * currentWeight;
	}
	// Divide by weight
	average.x = (int)(average.x / totalWeight);
	average.y = (int)(average.y / totalWeight);

	// Return the average position
	return average;
}

void ColorTracker::pushOntoPositionHistory(Point p) {
	std::rotate(centerHistory.begin(), centerHistory.begin() + 1, centerHistory.end());
	centerHistory[0] = p;
}

ColorRange ColorTracker::getRedColorRange() {
	return this->red;
}

ColorRange ColorTracker::getWhiteColorRange() {
	return this->white;
}

Mat ColorTracker::getRedMask() {
	return this->redMask;
}

Mat ColorTracker::getWhiteMask() {
	return this->whiteMask;
}