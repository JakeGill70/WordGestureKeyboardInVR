// GestureKeyboard.Recording.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "VirtualKey.h"
#include <cmath>
#include "ColorRange.h"
#include "ColorTracker.h"
#include "FrameController.h"

using namespace std;
using namespace cv;

int main()
{
    std::cout << "AR keyboard\n Created by: Jake Gillenwater\n";

    // Accessor to Video Camera
    FrameController frameController;

    // Image buffer for manipulating the frame data
    Mat frameBuffer;

    // Red color range comes from trial and error
    ColorRange redColorRange(Scalar(150,125,50), Scalar(190,255,255));
    // White color range comes from trial and error
    ColorRange whiteColorRange(Scalar(0,0,200), Scalar(25,255,255));

    // Object used for tracking the tip of a red light pen
    ColorTracker colorTracker(redColorRange, whiteColorRange);

    const Scalar YELLOW(0, 255, 255);
    const Scalar GREEN(50, 255, 50);
    const Scalar BLUE(255, 50, 50);

    while (1) {
        // Capture the frame data
        frameBuffer = frameController.getFrameFromCamera();

        // Update the color tracker with the latest frame data
        colorTracker.update(frameBuffer);

        // Draw a circle highlighting the average tip of the pen over the last 3 frames
        FrameController::addCircleToFrame(frameBuffer, colorTracker.getAveragePosition(), YELLOW);

        // Draw a circle highlighting the average tip of the pen over the last 3 frames
        // with a bias towards newer positions
        FrameController::addCircleToFrame(frameBuffer, colorTracker.getBiasedPosition(), GREEN);

        // Draw a circle highlghting the current tip of the pen
        FrameController::addCircleToFrame(frameBuffer, colorTracker.getCurrentPosition(), BLUE);

        // Display
        cv::imshow("Video Camera (Mirrored)", frameBuffer);
        FrameController::displayFrame(frameBuffer, "Video Camera (Mirrored)");

        // These two are exclusively for debugging purposes
        FrameController::displayFrame(colorTracker.getRedMask(), "Thresh Mask (Red)");
        FrameController::displayFrame(colorTracker.getWhiteMask(), "Thresh Mask (White)");

        // Exit if 'ESC' is pressed
        int keyPressed = waitKey(33);

        if (waitKey(33) == 27) {
            break;
        }
    }
    return 0;
}
