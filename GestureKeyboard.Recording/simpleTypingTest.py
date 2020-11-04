import keyboard
import os
import random
import string
import time

words = []
with open('wordList.txt') as f:
    words = [line.rstrip() for line in f]

outFile = open("TypingTestResults.txt", "a")

while(len(words) > 0):

    wordToType = words.pop()

    os.system("cls")
    print(wordToType)

    startTime = time.time()

    word = input()

    endTime = time.time()

    elapsedTime_s = endTime - startTime

    if(word=="?"):
        break

    outFile.write(wordToType + ":" + word + ":" + str(elapsedTime_s) + ":" + str(word == wordToType))

outFile.close()

exit(5)