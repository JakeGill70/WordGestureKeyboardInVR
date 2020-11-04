#include "VirtualKey.h"
#include "ColorRange.h"
#include "ColorTracker.h"
#include "FrameController.h"
#include "LightPenTracker.h"

#include <map>
#include <fstream>
#include <sstream>
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

map<string, int> getColorRangeSettings() {
    map<string, int> settings;
    
    settings["redUH"] = 190;
    settings["redUS"] = 255;
    settings["redUV"] = 255;
    settings["redLH"] = 150;
    settings["redLS"] = 125;
    settings["redLV"] = 50;

    settings["whiteUH"] = 25;
    settings["whiteUS"] = 255;
    settings["whiteUV"] = 255;
    settings["whiteLH"] = 0;
    settings["whiteLS"] = 0;
    settings["whiteLV"] = 255;
    std::ifstream settingsFile("ColorRangeSettings.txt");

    if (settingsFile.is_open()) {
        string line;
        string name;
        string value;
        while (getline(settingsFile, line))
        {
            name = line.substr(0, line.find(":"));
            value = line.substr(line.find(":") + 1, line.length());
            settings[name] = stoi(value);
        }
    }

    return settings;
}

void setColorRangeSettings(map<string, int> settings) {
    fstream appendFileToWorkWith;
    appendFileToWorkWith.open("ColorRangeSettings.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    if (!appendFileToWorkWith)
    {
        appendFileToWorkWith.open("ColorRangeSettings.txt", fstream::in | fstream::out | fstream::trunc);
    }

    for (const auto& myPair : settings) {
        appendFileToWorkWith << myPair.first << ":" << myPair.second << "\n";
        
    }
    appendFileToWorkWith.close();
}

void LightPenTracker::run(vector<string> wordList, bool settingsMode) {
    // Accessor to Video Camera
    FrameController frameController;

    // Image buffer for manipulating the frame data
    Mat frameBuffer;

    map<string, int> settings = getColorRangeSettings();

    int redUH = settings["redUH"];
    int redUS = settings["redUS"];
    int redUV = settings["redUV"];
    int redLH = settings["redLH"];
    int redLS = settings["redLS"];
    int redLV = settings["redLV"];

    int whiteUH = settings["whiteUH"];
    int whiteUS = settings["whiteUS"];
    int whiteUV = settings["whiteUV"];
    int whiteLH = settings["whiteLH"];
    int whiteLS = settings["whiteLS"];
    int whiteLV = settings["whiteLV"];

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

        // Iterate and showcase words from wordlist
        if (!settingsMode) {
            // Draw the word from the wordlist
            FrameController::addWordToType(frameBuffer, wordList[wordIndex]);

            // Compute the next word in the word list
            isInputtingGesture = (colorTracker.getAveragePosition().x != 0 || colorTracker.getAveragePosition().y != 0);
            if (!isInputtingGesture && !wordIndexIsUpdated) {
                wordIndex++;
                wordIndexIsUpdated = true;
                saveGestureToBitmap(gesture, wordList[wordIndex - 1].append(".gesture.bmp").c_str(), frameController.getFrameWidth(), frameController.getFrameHeight());
                gesture.clear();
            }
            if (isInputtingGesture) {
                wordIndexIsUpdated = false;
                gesture.push_back(colorTracker.getBiasedPosition());
            }
        }
        else {
            isInputtingGesture = true;
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

        // Setting adjusters
        if (settingsMode) {
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

            threshMaskName = "Thresh Mask (White)";
            threshMaskSettingsName = threshMaskName + " Settings";
            FrameController::displayFrame(colorTracker.getWhiteMask(), threshMaskName);
            cv::namedWindow(threshMaskSettingsName);
            cv::createTrackbar("UpperH", threshMaskSettingsName, &whiteUH, 255);
            cv::createTrackbar("UpperS", threshMaskSettingsName, &whiteUS, 255);
            cv::createTrackbar("UpperV", threshMaskSettingsName, &whiteUV, 255);
            cv::createTrackbar("LowerH", threshMaskSettingsName, &whiteLH, 255);
            cv::createTrackbar("LowerS", threshMaskSettingsName, &whiteLS, 255);
            cv::createTrackbar("LowerV", threshMaskSettingsName, &whiteLV, 255);

            ColorRange red(Scalar(redLH, redLS, redLV), Scalar(redUH, redUS, redUV));
            ColorRange white(Scalar(whiteLH, whiteLS, whiteLV), Scalar(whiteUH, whiteUS, whiteUV));
            colorTracker.setRedColorRange(red);
            colorTracker.setWhiteColorRange(white);

        }

        // Exit if 'ESC' is pressed
        int keyPressed = waitKey(1);
        if (keyPressed == ESCAPE_KEY_CODE) {
            if (settingsMode) {
                // Update settings with latest values
                settings["redUH"] = redUH;
                settings["redUS"] = redUS;
                settings["redUV"] = redUV;
                settings["redLH"] = redLH;
                settings["redLS"] = redLS;
                settings["redLV"] = redLV;

                settings["whiteUH"] = whiteUH;
                settings["whiteUS"] = whiteUS;
                settings["whiteUV"] = whiteUV;
                settings["whiteLH"] = whiteLH;
                settings["whiteLS"] = whiteLS;
                settings["whiteLV"] = whiteLV;

                // Save settings to file
                setColorRangeSettings(settings);
            }
            //Close Windows
            cv::destroyAllWindows();
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
