// GestureKeyboard.Recording.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "VirtualKey.h"

using namespace std;
using namespace cv;

int main()
{
    std::cout << "Hello World!\n";

    VideoCapture cap = VideoCapture(0); // Accessor to Video Camera
    int frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    int frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);

    Mat frame = Mat::zeros(frameHeight,frameWidth, CV_8UC3); // Frame Buffer
    Mat frameBuffer = Mat::zeros(frameHeight, frameWidth, CV_8UC3); // Frame Buffer
    Mat thresh = Mat::zeros(frameHeight, frameWidth, CV_8UC3); // Color threshold mask

    const int centerHistorySize=3;
    vector<Point> centerHistory = vector<Point>(centerHistorySize);

    while (1) {
        // Store the frame data
        cap.read(frame); 

        // Mirror the image so that it acts like a mirror (Feels more intuitive when used)
        flip(frame, frame, 1); 

        // Start manipulating the image within the frame buffer
        // Smooth the image while maintaining sharp edges
        bilateralFilter(frame, frameBuffer, 5, 50, 25); 
        
        // Convert to HSV color space for better color referencing
        cvtColor(frameBuffer, frameBuffer, COLOR_BGR2HSV);

        // Create a mask of where a range of colors appear (Shades of red in HSV color space)
        inRange(frameBuffer, Scalar(150, 125, 50), Scalar(190, 255, 255), thresh);

        // TODO: Figure out how this works and explain it
        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

        if (!contours.empty()) {

            // Find the biggest shape (contour)
            int maxArea = 0;
            int bestContourIndex = 0;
            for (int i = 0; i < contours.size(); i++)
            {
                int currentArea = contourArea(contours[i]);
                if (currentArea > maxArea) {
                    maxArea = currentArea;
                    bestContourIndex = i;
                }
            }

            // Find the center of the shape (contour)
            Moments M = cv::moments(contours[bestContourIndex]); // TODO: Figure out how this works and explain it
            Point center(0, 0);
            if (M.m00 != 0) { // Protect against divde by 0 errors
                center = Point((int)(M.m10 / M.m00), (int)(M.m01 / M.m00));
            }
            
            // Draw a circle highlighting the center
            circle(frame, center, 5, Scalar(255, 255, 255), -1);

            // Find the average center of the last 3 frames
            Point average(0, 0);
            for (int i = 0; i < centerHistory.size(); i++) {
                average.x += centerHistory[i].x;
                average.y += centerHistory[i].y;
            }
            average = average / centerHistorySize;

            // Shift values down for next iteration through the loop
            std::rotate(centerHistory.begin(), centerHistory.begin()+1, centerHistory.end());
            centerHistory[0] = center;

            // Draw a circle highlighting the average center
            circle(frame, average, 5, Scalar(0, 255, 255), 3);

        }

        // Display
        cv::imshow("Video Camera (Mirrored)", frame);
        cv::imshow("Thresh Mask (Red Marker)", thresh);

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
