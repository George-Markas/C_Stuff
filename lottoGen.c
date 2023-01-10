#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "b447.c"

#define POOL_SIZE 49
#define LOTTO_SIZE 6

//rand() % (max_number + 1 - minimum_number) + minimum_number

int main (void) {

    struct timeval t1;
    gettimeofday (&t1, NULL);
    srand (t1.tv_usec * t1.tv_sec);

    int lotto[LOTTO_SIZE];
    int pool[POOL_SIZE], temp;

    for (int i = 0; i < LOTTO_SIZE; i++) {
        lotto[i] = 0;
    }

    for (int i = 0; i < POOL_SIZE; i++) {
        pool[i] = i + 1;
    }

    for (int i = 0; i < LOTTO_SIZE; i++) {
        do{
            temp = rand() % POOL_SIZE;
        }while(pool[temp] == 0);
        lotto[i] = pool[temp];
        pool[temp] = 0;
    }

    for (int i = 0; i < LOTTO_SIZE - 1; i++) {
        for (int j = 0; j < LOTTO_SIZE - 1 - i; j++) {
            if (lotto[j] < lotto[j + 1]) {
                xorSwap(&lotto[j], &lotto[j + 1]);
            }
        }
    }

    printf("Generated lottery numbers: \n");
    printArray (lotto, LOTTO_SIZE);

    return 0;
}