/*

      ____                         _
     / __ \ _  __ ___  ____ _  __ (_)___  _    __
    / /_/ /| |/ // -_)/ __/| |/ // // -_)| |/|/ /
    \____/ |___/ \__//_/   |___//_/ \__/ |__,__/

    Info stored as 16 bit unsigned short integers.

    The 7 most significant bits store the voter's age (possible values are 0 - 127 but only 18 through 99 are valid).

    The next 2 bits store the voter's gender with these values being possible & valid: 1 (Male), 2 (Female), 3 (N/A).

    The 7 least significant bits store the vote itself, with each unique bit representing whether a candidate
    (out of the 7) has been voted for or not (with 1 and 0 values respectively). The least significant bit represents
    candidate #6, the second least significant bit candidate #5 etc.

*/

#include <stdlib.h>
#include <stdio.h>
#include "b447.c"

#define FILENAME "votes.dat"

int main (void) {

    FILE * filePointer;
    unsigned short fileEmpty;

    filePointer = fopen (FILENAME, "r"); // Opening votes.dat file to read its contents

    // Checking if votes.dat exists, exiting the programme if the file is non-existent.

    if (filePointer == NULL) {
        fclose (filePointer);
        printf ("Error: %s can not be read!\n", FILENAME);
        exit (EXIT_FAILURE);
    }

    /* Checking if votes.dat is empty and exiting the programme if it is. Sets the file position to the end of the file.
    If said position is 0 it naturally means the file is empty. */

    fseek (filePointer,0,SEEK_END);
    fileEmpty = ftell(filePointer);

    if (fileEmpty == 0) {
        fclose(filePointer);
        printf("Error: %s is empty, exiting programme...\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    /* Loops till the End-of-File indicator associated with the stream is set. Checks for newlines and adds them up to
    the voter count since each line change indicates a new info entry. */

    rewind (filePointer);

    size_t lineCount = 0;
    int charBuffer, hexBuffer;

    while ((charBuffer = getc (filePointer)) != EOF) {
        if (charBuffer == '\n') {
            lineCount++;
        }
    }

    rewind(filePointer);
    char *stringBuffer = calloc(6, sizeof(char));

    // Allocating space for the array containing the addresses of the bit encoded voter info.

    unsigned short** voterData = calloc(lineCount, sizeof(unsigned short*));

    for (int i = 0; i < lineCount; i++) {
        fgets (stringBuffer, 7, filePointer);
        sscanf (stringBuffer,"0x%x", &hexBuffer);
        voterData[i] = hexBin(&hexBuffer);
    }

    free(stringBuffer);

    fclose (filePointer);

    free (voterData);
    return (EXIT_SUCCESS);
}


