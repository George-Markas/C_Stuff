
//  Info stored as 16 bit unsigned short integers.

//  The 7 most important bits store the voter's age (possible values are 0 - 127 but only 18 through 99 are valid).

//  The next 2 bits store the voter's gender with these values being possible & valid: 1 (Male), 2 (Female), 3 (N/A).

//  The 7 least important bits store the vote itself, with each unique bit representing whether a candidate (out of the 7) has been voted for or not (with 1 and 0 values respectively).
//  The least important bit represents candidate #6, the second least important bit candidate #5 etc.

#include <stdlib.h>
#include <stdio.h>
#include "gcsheet.h"

int main(void){

    FILE * filePointer;
    int voterCount = 1;
    unsigned short fileEmpty = 1;

    filePointer = fopen("votes.dat", "r"); // Opening votes.dat file to read its contents

    // Checking if votes.dat exists, exiting the programme if the file is non-existent.

    if(filePointer == NULL){
        fclose(filePointer);
        printf("Error: votes.dat can not be read!\n");
        exit(-1);
    }

    // Checking if votes.dat is empty and exiting the programme if it is. Sets the file position to the end of the file. If said position is 0 it naturally means the file is empty.

    fseek(filePointer,0,SEEK_END);
    fileEmpty = ftell(filePointer);
    if(fileEmpty == 0){
        fclose(filePointer);
        printf("Error: votes.dat is empty, exiting programme...\n");
        exit(-1);
    }

    // Loops till the End-of-File indicator associated with the stream is set. Checks for newlines and adds them up to the voter count since each line change indicates a new info entry.
    // The amount of voter entries is the number of newlines + 1 since there's no newline for the last entry of the votes.dat file.

    while(feof(filePointer) == 0){
        if(fgetc(filePointer) == '\n'){
            voterCount++;
        }
    }

    fclose(filePointer);

    printf("Lines counted: %d\n",voterCount); // for debug purposes, to be deleted later.

    int* voterData = (int*) malloc(voterCount * sizeof(unsigned short)); // Allocating space for the array containing the voter info (number of voters * size needed for an unsigned short int).

    printArray(voterData, voterCount); // for debug purposes, to be deleted later.

    free(voterData);
    return (0);
}


