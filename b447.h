/*

     /$$       /$$   /$$ /$$   /$$ /$$$$$$$$
    | $$      | $$  | $$| $$  | $$|_____ $$/
    | $$$$$$$ | $$  | $$| $$  | $$     /$$/
    | $$__  $$| $$$$$$$$| $$$$$$$$    /$$/
    | $$  \ $$|_____  $$|_____  $$   /$$/
    | $$  | $$      | $$      | $$  /$$/
    | $$$$$$$/      | $$      | $$ /$$/
    |_______/       |__/      |__/|__/

*/

#include <stdio.h>
#include <stdlib.h>

#ifndef B447_H
#define B447_H

void xorSwap (int* a, int* b);

void printArray (int* array, int arraySize);

void asciiArt (const char* fileName);

int binDec (const unsigned short *bitStorage, int bitCount);

int* hexBin (const unsigned long *hexInput);

int raisePower (int base, int exponent);

#endif /* B447_H */