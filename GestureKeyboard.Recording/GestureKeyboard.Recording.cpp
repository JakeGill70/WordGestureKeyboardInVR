// GestureKeyboard.Recording.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LightPenTracker.h"
#include <vector>
#include "Bitmap.h"
#include <conio.h>

using namespace std;

void runTraditionalTypingTest(int si, int ei);
void runGestureTypingTest(LightPenTracker* lpt, vector<string> wordList, int si, int ei);
void runGestureSetup(LightPenTracker* lpt, vector<string> wordList);
vector<string> getWordList();
void ClearScreen();

int main()
{
    std::cout << "AR keyboard\n Created by: Jake Gillenwater\n\n";

    LightPenTracker* lpt = new LightPenTracker();

    vector<string> wordList = getWordList();

    std::string menu = "";
    menu += "[1] Setup\n";
    menu += "[2] Traditional Typing Test(Part 1)\n";
    menu += "[3] Traditional Typing Test(Part 2)\n";
    menu += "[4] WGK Typing Test (Part 1)\n";
    menu += "[5] WGK Typing Test (Part 2)\n";
    menu += "[6] WGK Typing Test(Part 3)\n";
    menu += "[7] WGK Typing Test(Part 4)\n";
    menu += "[8] Exit\n";

    std::string input;
    int inputVal;
    bool isRunning = true;

    while (isRunning) {

        inputVal = 0;

        ClearScreen();
        std::cout << menu;
        std::cin >> input;
        try {
            inputVal = stoi(input);
        }
        catch (invalid_argument e) {
            std::cout << "Menu option " << input << " is unavailable.\n";
        }

        switch (inputVal) {
            case 1:
                runGestureSetup(lpt, wordList);
                break;
            case 2:
                runTraditionalTypingTest(0, 249);
                break;
            case 3:
                runTraditionalTypingTest(250, 500);
                break;
            case 4:
                runGestureTypingTest(lpt, wordList, 0, 249);
                break;
            case 5:
                runGestureTypingTest(lpt, wordList, 250, 500);
                break;
            case 6:
                runGestureTypingTest(lpt, wordList, 0, 249);
                break;
            case 7:
                runGestureTypingTest(lpt, wordList, 250, 500);
                break;
            case 8:
                isRunning = false;
                break;
            default:
                std::cout << "Menu option " << input << " is unavailable.\n";
                break;
        }
    }
    
    return 0;
}

void runTraditionalTypingTest(int si, int ei) {
    // I know, I know... I'm not happy about this either,
    // but there will be time to refactor it into something
    // more effecient and more secure after I get the core
    // functionality working.
    system("python simpleTypingTest.py");
}

void runGestureTypingTest(LightPenTracker* lpt, vector<string> wordList, int si, int ei) {
    lpt->run(wordList);
}

void runGestureSetup(LightPenTracker* lpt) {
    lpt->setup();
}

vector<string> getWordList() {
    int wordListSize = 1000;
    vector<string> wordList;
    std::ifstream wordListInFile("wordList.txt");

    string line;
    for (int i = 0; i < wordListSize; i++)
    {
        getline(wordListInFile, line);
        wordList.push_back(line);
    }

    return wordList;
}

void ClearScreen()
{
    // I hate C++ sometimes...
    // Source: https://www.cplusplus.com/articles/4z18T05o/
    for (int n = 0; n < 10; n++) {
        printf("\n\n\n\n\n\n\n\n\n\n");
    }
}