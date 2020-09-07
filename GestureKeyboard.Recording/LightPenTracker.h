#pragma once
#ifndef LIGHT_PEN_TRACKER_H
#define LIGHT_PEN_TRACKER_H

#include <vector>

class LightPenTracker
{
public:
	void run(std::vector<std::string> wordList);
	int wordIndex;
};

#endif