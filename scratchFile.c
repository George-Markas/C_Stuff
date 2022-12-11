#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hexToBinary(char *hexString) {

    size_t length = strlen(hexString);

    for (int i = 0; i < length; i++) {

        int hexInteger = strtol(hexString, NULL, 16);

        for (int j = 3; j >= 0; j--) {
            printf("%d", (hexInteger >> j) & 1);
        }
    }
}

int main(void) {

    char hexString[16] = {0};

    printf("Enter a hexadecimal number: \n");

    scanf("%s", hexString);

    hexToBinary(hexString);

    return (EXIT_SUCCESS);
}
