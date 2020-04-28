#include "VirtualKeyboard.h"
#include <opencv2\core\types.hpp>


using namespace cv;
using namespace std;

VirtualKeyboard::VirtualKeyboard(Point position, Point size, int rowOffsets[]) {
	this->initKeys();
}

void VirtualKeyboard::drawKeyboard(Mat inputOutputArray)
{
}

void VirtualKeyboard::setKeyColor(Scalar c)
{
}

void VirtualKeyboard::setFontColor(Scalar c)
{
}

void VirtualKeyboard::setRowOffsets(int rowOffsets[])
{
}

VirtualKey VirtualKeyboard::getKey(int i)
{
	return VirtualKey();
}

VirtualKey VirtualKeyboard::getKey(string letter)
{
	return VirtualKey();
}

void VirtualKeyboard::initKeys() {

}