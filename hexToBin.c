#include <stdio.h>
#include <stdlib.h>

int main (void) {

    unsigned int hexNumber, digitBuffer, separatorMask = 0xf000;

    printf("Input hexadecimal number: \n");
    scanf("%x", &hexNumber);

    for (int i = 0; i < 4; i++) {
        digitBuffer = (hexNumber & separatorMask);  // Using bit-masking to zero out all digits besides the desired one

        for (int j = 3 - i; j > 0; j--) {   // Bit-shifting (3 - digits already processed) times to remove excess zeros, perfectly isolating the desired digit
            digitBuffer >>= 4;
        }

        unsigned int binaryMask = 0x8;

        for (int k = 0; k < 4; k++) {   // Using another bit-mask to get the value of each individual bit of the isolated digit and printing it in essentially binary form.
            if (digitBuffer & binaryMask) {
                putchar('1');
            }
            else {
                putchar('0');
            }
            binaryMask >>= 1;
        }
        separatorMask >>= 4;
    }

    return (EXIT_SUCCESS);
}