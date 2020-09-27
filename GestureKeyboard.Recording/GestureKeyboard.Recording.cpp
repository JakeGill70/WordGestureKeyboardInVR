// GestureKeyboard.Recording.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LightPenTracker.h"
#include <vector>
#include "Bitmap.h"

using namespace std;

vector<string> getWordList();

int main()
{
    std::cout << "AR keyboard\n Created by: Jake Gillenwater\n\n";

    BitMap bmp;
    for (int x = 0; x < 35; x++)
    {
        bmp.setPixel(x, 0, 255, 0, 0);
    }
    bmp.writeToFile("test.bmp");
    return 0;

    LightPenTracker lpt;

    vector<string> wordList = getWordList();

    lpt.run(wordList);
    
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