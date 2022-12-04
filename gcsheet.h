#ifndef C_PROJECTS_GCSHEET_H
#define C_PROJECTS_GCSHEET_H

void xorSwap(int* x, int* y) {
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}

void printArray(int* array, int arraySize){
    for(int i = 0; i < arraySize; i++){
        if(i == 0){
            printf("|");
        }
        printf("%02d|", array[i]);
    }
    printf("\n");
}

#endif
