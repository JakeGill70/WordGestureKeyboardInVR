#pragma once
#ifndef COLOR_RANGE_H
#define COLOR_RANGE_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class ColorRange
{
public:
	ColorRange();
	ColorRange(cv::Scalar min, cv::Scalar max);

	void setMin(cv::Scalar c);
	void setMax(cv::Scalar c);
	cv::Scalar getMin();
	cv::Scalar getMax();

private:
	cv::Scalar minHSV;
	cv::Scalar maxHSV;
};
#endif