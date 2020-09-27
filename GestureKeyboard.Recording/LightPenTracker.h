#pragma once
#ifndef LIGHT_PEN_TRACKER_H
#define LIGHT_PEN_TRACKER_H

#include <vector>
#include <opencv2/core/core.hpp>

class LightPenTracker
{
public:
	void run(std::vector<std::string> wordList);
	void saveGestureToBitmap(std::vector<cv::Point> gesture, const char* filename, int maxWidth, int maxHeight);
	int wordIndex;
};

#endif