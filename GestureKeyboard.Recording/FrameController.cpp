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

void FrameController::addCircleToFrame(cv::Mat frame, cv::Point position, cv::Scalar color) {
	int radius = 5;
	int thickness = 3;
	cv::circle(frame, position, radius, color, thickness);
}