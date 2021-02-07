import keyboard
import os
import random
import string
import time
import sys

# Build command:
# pyinstaller --onefile .\simpleTypingTest.py --workpath .\stt\build --distpath .\stt\dist

# Get command line args
wordListFileName = sys.argv[1]
resultsFileName = sys.argv[2]
wordListStartIndex = int(sys.argv[3])
wordListEndIndex = int(sys.argv[4])

# Pull the word list from the file
words = []
with open(wordListFileName) as f:
    words = [line.rstrip() for line in f]

# Set the words list to only use the required subset
words = words[wordListStartIndex:wordListEndIndex]

# Create the output file
outFile = open(resultsFileName, "a")

# Take the typing test
while(len(words) > 0):

    wordToType = words.pop()

    os.system("cls")
    print(wordToType)

    startTime = time.time()

    word = input()

    endTime = time.time()

    elapsedTime_s = endTime - startTime

    # Exit character for testing purposes
    if(word=="?"):
        break

    # Output all the necessary information to the output file
    # Notice that correct input/spelling can be checked after the fact
    outFile.write(wordToType + ":" + word + ":" + str(elapsedTime_s) + ":" + str(word == wordToType))

# Finish writing to the file and close it
outFile.close()

# Exit with a code 0
exit(0)