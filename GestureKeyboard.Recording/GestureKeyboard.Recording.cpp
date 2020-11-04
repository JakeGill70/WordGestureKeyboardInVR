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

vector<string> getWordList();
void ClearScreen();

int main()
{
    std::cout << "AR keyboard\n Created by: Jake Gillenwater\n\n";

    LightPenTracker* lpt = new LightPenTracker();

    vector<string> wordList = getWordList();

    std::string menu = "[1] Setup\n";
    menu += "[2] Traditional Typing Test(Part 1)\n[3] Traditional Typing Test(Part 2)\n";
    menu += "[4] WGK Typing Test (Part 1)\n[5] WGK Typing Test (Part 2)\n[6] WGK Typing Test (Part 3)\n[7] WGK Typing Test (Part 4)\n";
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
                lpt->run(wordList, true);
                break;
            case 2:
            case 3:
                // I know, I know... I'm not happy about this either,
                // but there will be time to refactor it into something
                // more effecient and more secure after I get the core
                // functionality working.
                system("python simpleTypingTest.py");
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                lpt->run(wordList, false);
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