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

using namespace std;
using namespace cv;

int main()
{
    std::cout << "AR keyboard\n Created by: Jake Gillenwater\n";

    // Accessor to Video Camera
    VideoCapture cap = VideoCapture(0); 
    int frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    int frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);

    // Image retrieved from the video gamera
    Mat frame = Mat::zeros(frameHeight,frameWidth, CV_8UC3);

    // Red color range comes from trial and error
    ColorRange redColorRange(Scalar(150,125,50), Scalar(190,255,255));
    // White color range comes from trial and error
    ColorRange whiteColorRange(Scalar(0,0,200), Scalar(25,255,255));

    // Object used for tracking the tip of a red light pen
    ColorTracker colorTracker(redColorRange, whiteColorRange);

    while (1) {
        // Capture the frame data
        cap.read(frame); 

        // Mirror the image so feels more intuitive to use
        flip(frame, frame, 1); 

        // Update the color tracker with the latest frame data
        colorTracker.update(frame);

        // Draw a circle highlghting the current tip of the pen

        // Draw a circle highlighting the average tip of the pen over the last 3 frames
        circle(frame, colorTracker.getAveragePosition(), 5, Scalar(0, 255, 255), 3);

        // Display
        cv::imshow("Video Camera (Mirrored)", frame);

        // These two are exclusively for debugging purposes
        cv::imshow("Thresh Mask (Red)", colorTracker.getRedMask());
        cv::imshow("Thresh Mask (White)", colorTracker.getWhiteMask());

        // Exit if 'ESC' is pressed
        if (waitKey(33) == 27) {
            break;
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
