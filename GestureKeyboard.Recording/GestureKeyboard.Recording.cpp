// GestureKeyboard.Recording.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LightPenTracker.h"

using namespace std;

int main()
{
    std::cout << "AR keyboard\n Created by: Jake Gillenwater\n\n";

    LightPenTracker lpt;

    lpt.run();
    
    return 0;
}
