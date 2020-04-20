#pragma once
#include "ColorRange.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

ColorRange::ColorRange() {
	this->setMin(Scalar(0, 0));
	this->setMax(Scalar(0, 0));
}

ColorRange::ColorRange(Scalar min, Scalar max) {
	this->setMin(min);
	this->setMax(max);
}

Scalar ColorRange::getMax(){
	return this->maxHSV;
}

Scalar ColorRange::getMin() {
	return this->minHSV;
}

void ColorRange::setMax(Scalar c) {
	this->maxHSV = c;
}

void ColorRange::setMin(Scalar c) {
	this->minHSV = c;
}