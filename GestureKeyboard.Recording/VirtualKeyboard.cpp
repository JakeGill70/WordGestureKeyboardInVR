#include "VirtualKeyboard.h"
#include <opencv2\core\types.hpp>


using namespace cv;
using namespace std;

VirtualKeyboard::VirtualKeyboard(Point startPosition, Point keySize, char letters[], int rowOffsets[]) {

	// This function creates the keys
	this->initKeys(startPosition, keySize);
}

void VirtualKeyboard::drawKeyboard(Mat inputOutputArray)
{
	// Draw each key
	for (int i = 0; i < this->numberOfKeys; i++)
	{
		this->keys->drawKey(inputOutputArray);
	}
}

void VirtualKeyboard::setKeyColor(Scalar c)
{
	// Change the button color value foreach key
	for (int i = 0; i < this->numberOfKeys; i++)
	{
		this->keys[i].buttonColor = c;
	}
}

void VirtualKeyboard::setFontColor(Scalar c)
{
	// Change the button color value foreach key
	for (int i = 0; i < this->numberOfKeys; i++)
	{
		this->keys[i].buttonColor = c;
	}
}

void VirtualKeyboard::setKeySize(cv::Point keySize)
{
	// Create a pointer to a key's transform
	//	to make it easier to reference a key's transform property.
	Rect* keyTransform;

	// Change the size of each key
	for (int i = 0; i < this->numberOfKeys; i++)
	{
		keyTransform = &(this->keys[i].transform);
		keyTransform->width = keySize.x;
		keyTransform->height = keySize.y;
	}
}

VirtualKey VirtualKeyboard::getKey(int i)
{
	return this->keys[i];
}

VirtualKey VirtualKeyboard::getKey(char letter)
{
	// TODO: Have some sort of error handling or check to ensure that the argument letter exists as a key.
	// Linearally search for the key with the matching letter
	for (int i = 0; i < this->numberOfKeys; i++)
	{
		if (this->keys[i].letter == letter) {
			return this->keys[i];
		}
	}
}

void VirtualKeyboard::initKeys(Point startPosition, Point keySize) {
	// TODO: Make this more extendable by allowing multiple keyboard layouts
	char letters[] = "qwertyuiop|asdfghjkl|zxcvbnm";
	int rowOffsets[] = { 0, 20, 40 };
	int rowOffsetIndex = 0;
	int keyKerning = 3;

	// Determine the size of the argument array.
	//	This will tell us the maximum number of keys to create.
	//	Note: this number will be reduced in the for loop below
	//	whenever a row delimiter is found within the string.
	this->numberOfKeys = sizeof(letters) / sizeof(char);

	// Allocate memory for all these new virtual keys
	this->keys[this->numberOfKeys];

	// Use a rect to set the position and size of each newly created key
	Rect keyTransform(startPosition.x, startPosition.y, keySize.x, keySize.y);

	// Foreach letter in letters, create a virtual key for it
	for (int i = 0; i < this->numberOfKeys; i++)
	{
		if (letters[i] == '|') {
			rowOffsetIndex++;
			keyTransform.x = startPosition.x;
			keyTransform.x += rowOffsets[rowOffsetIndex];
			keyTransform.y += keySize.y + keyKerning;
			this->numberOfKeys--;
		}
		else {
			this->keys[i] = VirtualKey(letters[i], keyTransform);
			keyTransform.x += keyKerning;
		}
	}
}