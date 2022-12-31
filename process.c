// Info stored as 16 bit unsigned short integers.

// The 7 most significant bits store the voter's age (possible values are 0 - 127 but only 18 through 99 are valid).

// The next 2 bits store the voter's gender with these values being possible & valid: 1 (Male), 2 (Female), 3 (N/A).

/* The 7 least significant bits store the vote itself, with each unique bit representing whether a candidate
(out of the 7) has been voted for or not (with 1 and 0 values respectively). The least significant bit represents
candidate #6, the second least significant bit candidate #5 etc. */

#include <stdlib.h>
#include <stdio.h>
#include "gcsheet.h"

int main (void) {

    FILE * filePointer;
    unsigned short fileEmpty;

    filePointer = fopen ("votes.dat", "r"); // Opening votes.dat file to read its contents

    // Checking if votes.dat exists, exiting the programme if the file is non-existent.

    if (filePointer == NULL) {
        fclose (filePointer);
        printf ("Error: votes.dat can not be read!\n");
        exit (EXIT_FAILURE);
    }

    /* Checking if votes.dat is empty and exiting the programme if it is. Sets the file position to the end of the file.
    If said position is 0 it naturally means the file is empty. */

    fseek (filePointer,0,SEEK_END);
    fileEmpty = ftell(filePointer);

    if (fileEmpty == 0) {
        fclose(filePointer);
        printf("Error: votes.dat is empty, exiting programme...\n");
        exit(EXIT_FAILURE);
    }

    /* Loops till the End-of-File indicator associated with the stream is set. Checks for newlines and adds them up to
    the voter count since each line change indicates a new info entry. */

    rewind (filePointer);

    int lineCount = 0;
    int charTube;

    for (charTube = getc (filePointer); charTube != EOF; charTube = getc(filePointer)) {
        if (charTube == '\n'){
            lineCount++;
        }
    }

    fclose (filePointer);

    printf ("Lines counted: %d\n",lineCount); // for debug purposes, to be deleted later.

    // Allocating space for the array containing the voter info (number of voters * size of an unsigned short int).

    int* voterData = (int*) malloc(lineCount * sizeof(unsigned short));

    printArray (voterData, lineCount); // for debug purposes, to be deleted later.

    free (voterData);
    return (EXIT_SUCCESS);

}


