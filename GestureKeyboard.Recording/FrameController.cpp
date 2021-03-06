#include "FrameController.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ColorRange.h"

using namespace std;
using namespace cv;

FrameController::FrameController() {
	// Accessor to the video camera
	this->cap = VideoCapture(0);
	// Get properties about the video stream
	this->frameHeight = (int) cap.get(CAP_PROP_FRAME_HEIGHT);
	this->frameWidth = (int) cap.get(CAP_PROP_FRAME_WIDTH);
	// See getFrameFromCamera for more information for why this field exists
	this->lastFrameFromCamera = Mat::zeros(this->frameHeight, this->frameWidth, CV_8UC3);
}

Mat FrameController::getFrameFromCamera() {
	// Keep lastFrameFromCamera as a property instead of a local
	//		So you don't have to waste time reallocating memory
	//		each time this is called, ie every frame.
	this->cap.read(this->lastFrameFromCamera);

	// Mirror the image so feels more intuitive to use
	flip(lastFrameFromCamera, lastFrameFromCamera, 1);

	return lastFrameFromCamera;
}

int FrameController::getFrameHeight() {
	return this->frameHeight;
}

int FrameController::getFrameWidth() {
	return this->frameWidth;
}

void FrameController::displayFrame(cv::Mat frame, string windowName) {
	cv::imshow(windowName, frame);
}

void FrameController::displayFrameWithSliders(cv::Mat frame, string windowName, vector<int> &sliderValues) {
	cv::imshow(windowName, frame);
	string settingsName = windowName + " Settings";
	cv::namedWindow(settingsName);

	// Create sliders
	cv::createTrackbar("UpperH", settingsName, &sliderValues[0], 255);
	cv::createTrackbar("UpperS", settingsName, &sliderValues[1], 255);
	cv::createTrackbar("UpperV", settingsName, &sliderValues[2], 255);
	cv::createTrackbar("LowerH", settingsName, &sliderValues[3], 255);
	cv::createTrackbar("LowerS", settingsName, &sliderValues[4], 255);
	cv::createTrackbar("LowerV", settingsName, &sliderValues[5], 255);

	// Update slider values
	sliderValues[0] = cv::getTrackbarPos("UpperH", settingsName);
	sliderValues[1] = cv::getTrackbarPos("UpperS", settingsName);
	sliderValues[2] = cv::getTrackbarPos("UpperV", settingsName);
	sliderValues[3] = cv::getTrackbarPos("LowerH", settingsName);
	sliderValues[4] = cv::getTrackbarPos("LowerS", settingsName);
	sliderValues[5] = cv::getTrackbarPos("LowerV", settingsName);
	
}

void FrameController::addCircleToFrame(cv::Mat frame, cv::Point position, cv::Scalar color) {
	int radius = 5;
	int thickness = 3;
	cv::circle(frame, position, radius, color, thickness);
}

void FrameController::addWordToType(cv::Mat frame, string word) {
	cv::putText(frame, word, Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255));
}