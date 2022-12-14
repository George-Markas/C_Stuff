#include <stdio.h>
#include <string.h>

 void hexToBinary (char *hexString) {

    size_t stringLength= strlen(hexString);
    int bitStorage[sizeof(int) * stringLength];
    int quadOffset = 0;

    for (int i = 0; i < stringLength; i++) {

        int coefficient = 8;

        for (int j = 0; j < 4; j++) {

            if (hexString[i] & coefficient) {
                bitStorage[j + quadOffset] = 1;
            }else{
                bitStorage[j + quadOffset] = 0;
            }
            coefficient >>= 1;
        }
        quadOffset += 4;
    }

}

int main(void){

    char test[4];
    printf("Input test hex: \n");
    scanf("%s", test);
    hexToBinary(test);

}


