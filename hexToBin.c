#include <stdio.h>
#include <stdlib.h>

/* Function that takes a hex number as an unsigned short input, converts it to binary bits (1 & 0), stores said bits in
memory and returns a pointer with the memory address. */

// WARNING: make sure to deallocate the used memory by using free() since this function doesn't do so.

int* hexToBin (const unsigned short *hexInput) {

    unsigned short digitBuffer, separatorMask = 0xf000;
    unsigned short hexNumber = *hexInput;

    unsigned short digitCount = 0;
    digitBuffer = hexNumber;

    // determining the number of digits of the inputted hex number

    while (digitBuffer) {
        digitCount++;
        digitBuffer >>= 4;
    }

    unsigned short quadOffset = 0;
    int *bitStorage = (int*) malloc(sizeof(int) * digitCount);

    for (int i = 0; i < digitCount; i++) {

        // Using bit-masking to zero out all digits besides the desired one

        digitBuffer = (hexNumber & separatorMask);

        /* Bit-shifting ( (number of digits - 1) - digits already processed) times to remove excess zeros, perfectly
        isolating the desired digit */

        for (int j = (digitCount -1) - i; j > 0; j--) {
            digitBuffer >>= 4;
        }

        unsigned int binaryMask = 0x8;

        /* Using another bit-mask to get the value of each individual bit of the isolated digit and printing it in
        essentially binary form. */

        for (int k = 0; k < 4; k++) {
            if (digitBuffer & binaryMask) {
                bitStorage[k + quadOffset] = 1;
            }
            else {
                bitStorage[k + quadOffset] = 0;
            }
            binaryMask >>= 1;
        }
        separatorMask >>= 4;
        quadOffset += 4;
    }

    return (bitStorage);
}

int main (void) {

    unsigned short hexNumber;
    int* bitStorage = NULL;
    printf("Input hex number: \n");
    scanf("%hx", &hexNumber);
    bitStorage = hexToBin(&hexNumber);

    for (int i = 0; i < 16; i++) {
        printf("%d", bitStorage[i]);
    }

    free(bitStorage);
    return (EXIT_SUCCESS);
}