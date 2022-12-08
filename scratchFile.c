#include <stdio.h>
#include "gcsheet.h"
int main(void){

    int array[4];
    unsigned short int hexNumber;

    printf("Input 4-bit hex number: \n");
    scanf("%hu", &hexNumber);

    int rightPusher, leftPusher;
    rightPusher = 10000;
    leftPusher = 1000;

    for(int i = 0; i < 4; i++){
        array[i] = (hexNumber % rightPusher) / leftPusher;
        rightPusher /= 10;
        leftPusher /= 10;
    }

    printArray(array,4);

    int coefficient = 1;

    for(int i = 3; i > 0; i--){
        array[i] = array[i] * coefficient;
        coefficient <<= 4;
    }

    printArray(array,4);
}