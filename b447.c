/* Simple swap() implementation utilizing bitwise XOR */

void xorSwap (int* a, int* b) {
    if (*a != *b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

/* Simple function that prints the elements of an integer array, each seperated by vertical lines */

void printArray(int* array, int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        if (!i) {
            printf ("|");
        }
        printf ("%02d|", array[i]);
    }
    printf ("\n");
}

/* Function that takes a hex number as an unsigned long input, converts it to binary bits (1 & 0), stores said bits in
memory and returns a pointer with the memory address. */

// WARNING: make sure to deallocate the used memory by using free() since this function doesn't do so.

unsigned short* hexBin (const unsigned long *hexInput) {

    unsigned long digitBuffer;
    unsigned long hexNumber = *hexInput;

    unsigned short digitCount = 0;
    digitBuffer = hexNumber;

    // determining the number of digits of the inputted hex number

    while (digitBuffer) {
        digitCount++;
        digitBuffer >>= 4;
    }

    unsigned long separatorMask = 0xf;

    // Initializing bitmask based on the number of digits of the inputted hexadecimal number.

    for (int i = 0; i < (digitCount - 1); i++) {
        separatorMask <<= 4;
    }

    unsigned short quadOffset = 0;
    unsigned short *bitStorage = (unsigned short*) malloc(sizeof (unsigned short) * digitCount);

    if (bitStorage == NULL) {
        printf ("Memory allocation failure, exiting... \n");
        exit (EXIT_FAILURE);
    }

    for (int i = 0; i < digitCount; i++) {

        // Using bit-masking to zero out all digits besides the desired one

        digitBuffer = (hexNumber & separatorMask);

        /* Bit-shifting ( (number of digits - 1) - digits already processed ) times to remove excess zeros, fully
        isolating the desired digit */

        for (int j = (digitCount -1) - i; j > 0; j--) {
            digitBuffer >>= 4;
        }

        unsigned short binaryMask = 0x8;

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



