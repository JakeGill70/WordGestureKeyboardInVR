#include "VirtualKeyboard.h"
#include <opencv2/core/types.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdexcept>


using namespace cv;
using namespace std;

VirtualKeyboard::VirtualKeyboard(Point startPosition, Point keySize, int numberOfLetters, char letters[], int rowOffsets[]) {
	
	// Determines how much each new row of keys should be offset to the right
	int rowOffsetIndex = 0;

	// Determine the amount of spacing between each key
	int keyKerning = 3;

	// Determine the size of the argument array.
	//	This will tell us the maximum number of keys to create.
	//	Note: this number will be reduced in the for loop below
	//	whenever a row delimiter is found within the string.
	this->numberOfKeys = numberOfLetters;

	// Allocate memory for all these new virtual keys
	this->keys[numberOfLetters] = {};

	// Use a rect to set the position and size of each newly created key
	Rect keyTransform(startPosition.x, startPosition.y, keySize.x, keySize.y);

	int keyIndex = 0;

	// Foreach letter in letters, create a virtual key for it
	for (int i = 0; i < numberOfLetters; i++)
	{
		if (letters[i] == '|') {
			rowOffsetIndex++;
			keyTransform.x = startPosition.x;
			keyTransform.x += rowOffsets[rowOffsetIndex];
			keyTransform.y += keySize.y + keyKerning;
			this->numberOfKeys--;
		}
		else {
			this->keys[keyIndex] = VirtualKey(letters[i], keyTransform);
			keyIndex++;
			keyTransform.x += keySize.x + keyKerning;
		}
	}
}

void VirtualKeyboard::drawKeyboard(Mat* inputOutputArray)
{
	/*

	Niave drawing - will need to batch draw calls to make this work
	
	// Draw each key
	for (int i = 0; i < this->numberOfKeys; i++)
	{
		this->keys->drawKey(*inputOutputArray);
	}

	*/

	Mat overlay;
	inputOutputArray->copyTo(overlay);

	Scalar buttonColor = this->keys[0].buttonColor;

	VirtualKey* key;

	// Draw each key
	for (int i = 0; i < this->numberOfKeys; i++)
	{
		key = &(this->keys[i]);

		// Draw button
		rectangle(overlay, key->transform, buttonColor, -1);
		
		// Define Letter
		string textToDisplay;
		textToDisplay += key->letter;
		Point keyCorner = Point(key->transform.x, key->transform.y);
		int fontStyle = cv::FONT_HERSHEY_SIMPLEX;
		int fontScaling = 1;
		Scalar fontColor = key->fontColor;
		int lineThickness = 3;
		int lineType = cv::LINE_4;

		// Translate the position of the letter such that it is in the center of a button
		keyCorner.y += fontScaling * 20 + 5;
		keyCorner.x += 5;

		// Draw Letter
		cv::putText(overlay, textToDisplay, keyCorner, fontStyle, fontScaling, fontColor, lineThickness, lineType);
	}

	// Draw keyboard overlay
	double alpha = 0.33;
	addWeighted(overlay, alpha, *inputOutputArray, 1 - alpha, 0, *inputOutputArray);
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
	std::string errMsg = "Cannot map the letter ";
	errMsg += letter;
	errMsg += " to an index in keys[].";
	throw std::runtime_error(errMsg);

}