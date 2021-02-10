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
#include <windows.h>
#include <stdio.h>

using namespace std;

void runTraditionalTypingTest(int si, int ei);
void runGestureTypingTest(LightPenTracker* lpt, vector<string> wordList, int si, int ei);
void runGestureSetup(LightPenTracker* lpt);
vector<string> getWordList();
void clearScreen();

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

        clearScreen();
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
                runGestureSetup(lpt);
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
    // ! To work, note that you need to define "WINDOWS_IGNORE_PACKING_MISMATCH" under
    // ! Project Settings > C++ > Preprocessor > Preprocessor definitions

    STARTUPINFOA startInfo;
    PROCESS_INFORMATION procInfo;

    ZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);
    ZeroMemory(&procInfo, sizeof(procInfo));

    /*
    Cmd Line Args from the python script:
    wordListFileName = sys.argv[1]
    resultsFileName = sys.argv[2]
    wordListStartIndex = int(sys.argv[3])
    wordListEndIndex = int(sys.argv[4])
    */
    std::string wordListFileName = "wordList.txt ";
    std::string resultsFileName = "./SimpleTypingTestResults.txt ";
    std::string startIndex = to_string(si);
    std::string endIndex = to_string(ei);
    std::string strCmd = "python simpleTypingTest.py " + wordListFileName + resultsFileName + startIndex + " " + endIndex;
    LPSTR lpStrCmd = const_cast<char*>(strCmd.c_str());

    // Start the child process. 
    if (!CreateProcessA(
        NULL,           // No module name (use command line)
        lpStrCmd,       // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &startInfo,     // Pointer to STARTUPINFO structure
        &procInfo)      // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject(procInfo.hProcess, INFINITE);

    // Close process and thread handles. 
    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
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

void clearScreen()
{
    // I hate C++ sometimes...
    // Source: https://www.cplusplus.com/articles/4z18T05o/
    for (int n = 0; n < 10; n++) {
        printf("\n\n\n\n\n\n\n\n\n\n");
    }
}