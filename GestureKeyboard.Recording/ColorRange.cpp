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

vector<int> ColorRange::toIntArray()
{
	vector<int> vals(6);
	vals[0]= maxHSV[0];
	vals[1] = maxHSV[1];
	vals[2] = maxHSV[2];
	vals[3] = minHSV[0];
	vals[4] = minHSV[1];
	vals[5] = minHSV[2];
	return vals;
}

void ColorRange::fromIntArray(vector<int> arr)
{
	 maxHSV[0] = arr[0];
	 maxHSV[1] = arr[1];
	 maxHSV[2] = arr[2];
	 minHSV[0] = arr[3];
	 minHSV[1] = arr[4];
	 minHSV[2] = arr[5];
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