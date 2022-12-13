#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

void hexToBinary (char *hexString) {

    size_t characterLength= strlen(hexString);
    //int* bitStorage = (int*) malloc(characterLength * 4);
    int bitStorage[characterLength * 4];
    int q = 0;
    for (int i = 0; i < characterLength; i++) {
        int coefficient = 8;
        for (int j = 0; j < 4; j++) {
            bitStorage[j] = (hexString[i] & coefficient);
            coefficient >>= 1;
        }
        q += 4;
    }
    for (int i = 0; i < characterLength * 4; i++) {
        printf("%d", bitStorage[i]);
    }
    //free(bitStorage);
}

int main(void){
    char test[4];
    printf("Input test hex: \n");
    scanf("%s", test);
    hexToBinary(test);
}


