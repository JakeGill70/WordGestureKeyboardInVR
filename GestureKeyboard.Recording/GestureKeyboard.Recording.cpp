// GestureKeyboard.Recording.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LightPenTracker.h"

using namespace std;

int main()
{
    std::cout << "AR keyboard\n Created by: Jake Gillenwater\n\n";

    LightPenTracker lpt;

    string wordList[1000];
    std::ifstream wordListInFile("wordList.txt");

    string line;
    for (int i = 0; i < 1000; i++)
    {
        getline(wordListInFile, line);
        wordList[i] = line;
    }

    for (int i = 0; i < 25; i++)
    {
        cout << wordList[i] << "\n";
    }

    getline(cin, line);

    return 0;

    lpt.run();
    
    return 0;
}
