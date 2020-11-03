#include "VirtualKey.h"
#include "ColorRange.h"
#include "ColorTracker.h"
#include "FrameController.h"
#include "LightPenTracker.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include "VirtualKeyboard.h"

#include "Bitmap.h"

#define ESCAPE_KEY_CODE 27
#define SPACEBAR_KEY_CODE 32

using namespace std;
using namespace cv;

void LightPenTracker::run(vector<string> wordList) {
    // Accessor to Video Camera
    FrameController frameController;

    // Image buffer for manipulating the frame data
    Mat frameBuffer;

    int redUH =190, redUS=255, redUV=255;
    int redLH=150, redLS=125, redLV=50;

    // Red color range comes from trial and error
    ColorRange redColorRange(Scalar(150, 125, 50), Scalar(190, 255, 255));
    // White color range comes from trial and error
    ColorRange whiteColorRange(Scalar(0, 0, 200), Scalar(25, 255, 255));

    // Object used for tracking the tip of a red light pen
    ColorTracker colorTracker(redColorRange, whiteColorRange);

    const Scalar YELLOW(0, 255, 255);
    const Scalar GREEN(50, 255, 50);
    const Scalar BLUE(255, 50, 50);

    wordIndex = 0;
    char letters[] = "qwertyuiop|asdfghjkl|zxcvbnm";
    int numberOfLetters = sizeof(letters) - 1; // Must subtract 1 because ""-notation of char arrays automatically adds a null character
    int rowOffsets[3] = { 0, 20, 40 };
    Point startPosition(30, 140);
    Point keySize(55, 65);
    VirtualKeyboard virtualKeyboard(startPosition, keySize, numberOfLetters, letters, rowOffsets);

    bool wordIndexIsUpdated = false;
    bool isInputtingGesture = false;

    vector<cv::Point> gesture;

    while (1) {
        // Capture the frame data
        frameBuffer = frameController.getFrameFromCamera();

        // Update the color tracker with the latest frame data
        colorTracker.update(frameBuffer);

        // Draw the keyboard
        virtualKeyboard.drawKeyboard(&frameBuffer);

        // Draw the word from the wordlist
        FrameController::addWordToType(frameBuffer, wordList[wordIndex]);

        // Compute the next word in the word list
        isInputtingGesture = (colorTracker.getAveragePosition().x != 0 || colorTracker.getAveragePosition().y != 0);
        if (!isInputtingGesture && !wordIndexIsUpdated) {
            wordIndex++;
            wordIndexIsUpdated = true;
            saveGestureToBitmap(gesture, wordList[wordIndex-1].append(".gesture.bmp").c_str(), frameController.getFrameWidth(), frameController.getFrameHeight());
            gesture.clear();

            
        }
        if (isInputtingGesture) {
            wordIndexIsUpdated = false;
            gesture.push_back(colorTracker.getBiasedPosition());
        }

        // Draw a circle highlighting the average tip of the pen over the last 3 frames
        FrameController::addCircleToFrame(frameBuffer, colorTracker.getAveragePosition(), YELLOW);

        // Draw a circle highlighting the average tip of the pen over the last 3 frames
        // with a bias towards newer positions
        FrameController::addCircleToFrame(frameBuffer, colorTracker.getBiasedPosition(), GREEN);

        // Draw a circle highlghting the current tip of the pen
        FrameController::addCircleToFrame(frameBuffer, colorTracker.getCurrentPosition(), BLUE);

        // Display
        FrameController::displayFrame(frameBuffer, "Video Camera (Mirrored)");

        // These two are exclusively for debugging purposes
        string threshMaskName = "Thresh Mask (Red)";
        string threshMaskSettingsName = threshMaskName + " Settings";

        FrameController::displayFrame(colorTracker.getRedMask(), threshMaskName);
        cv::namedWindow(threshMaskSettingsName);
        cv::createTrackbar("UpperH", threshMaskSettingsName, &redUH, 255);
        cv::createTrackbar("UpperS", threshMaskSettingsName, &redUS, 255);
        cv::createTrackbar("UpperV", threshMaskSettingsName, &redUV, 255);

        cv::createTrackbar("LowerH", threshMaskSettingsName, &redLH, 255);
        cv::createTrackbar("LowerS", threshMaskSettingsName, &redLS, 255);
        cv::createTrackbar("LowerV", threshMaskSettingsName, &redLV, 255);

        ColorRange red(Scalar(redLH, redLS, redLV), Scalar(redUH, redUS, redUV));
        colorTracker.setRedColorRange(red);

        // Exit if 'ESC' is pressed
        int keyPressed = waitKey(1);
        if (keyPressed == ESCAPE_KEY_CODE) {
            break;
        }
    }
}

void LightPenTracker::saveGestureToBitmap(std::vector<cv::Point> gesture, const char* filename, int maxWidth, int maxHeight)
{
    BitMap bitMap;
    char* buffer = bitMap.getBmpBuffer();
    int bufferIndex = 0;
    for (int gestureIndex = 0; gestureIndex < gesture.size(); gestureIndex++)
    {
        short x = short(((float)gesture[gestureIndex].x / (float)maxWidth) * 4095);
        short y = short(((float)gesture[gestureIndex].y / (float)maxHeight) * 4095);;
        bitMap.setPixel(bufferIndex, x, y);
        bufferIndex += 3;
    }
    
    bitMap.writeToFile(filename);
}
