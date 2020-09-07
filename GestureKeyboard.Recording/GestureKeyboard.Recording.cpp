// GestureKeyboard.Recording.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LightPenTracker.h"
#include <vector>

using namespace std;

int main()
{
    std::cout << "AR keyboard\n Created by: Jake Gillenwater\n\n";

    LightPenTracker lpt;

    vector<string> wordList = getWordList();

    lpt.run();
    
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