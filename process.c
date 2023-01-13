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
#include <string.h>
#include "b447.c"

#define FILENAME "votes.dat"
#define NUM_CANDIDATES 7

int main (void) {

    FILE * filePointer;
    long fileStatus;

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
    fileStatus = ftell(filePointer);

    if (fileStatus == 0) {
        fclose(filePointer);
        printf("Error: %s is empty, exiting programme...\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    /* Loops till the End-of-File indicator associated with the stream is set. Checks for newlines and adds their count
    up to lineCount since each line change indicates a new data entry. The last line can be accompanied by a newline or
    left as is, the count remains consistent. */

    rewind (filePointer);

    size_t lineCount = 0;
    int charBuffer;

    while ((charBuffer = getc (filePointer)) != EOF) {
        if (charBuffer == '\n') {
            lineCount++;
        }
        else {
            charBuffer = getc (filePointer);
            if (charBuffer == EOF) {
                lineCount++;
            }
            ungetc (charBuffer, filePointer);
        }
    }

    /* Allocating space for the array containing the poll results. Data is stored in a pseudo-2D fashion and handled as
    follows: each candidate has the votes they received categorized in each of the 3 "columns" of his respective "row",
    with the 1st column being votes received from male voters, 2nd from female voters and 3rd from other respectively.
    Because a one dimensional array is used, the "columns" are represented by their position relative to the candidate's
    number.

    e.g. the number of votes candidate #2 received from female voters are stored in the ( (candidateNumber * 3) + 1 )th
    element of the array. */

    unsigned long hexBuffer;
    int gender, age, temp;
    size_t lengthCheck;
    unsigned short* bitStorage = NULL;

    char *stringBuffer = calloc(6, sizeof(char));
    int *newlineSkip = (int*) malloc(sizeof (char));
    int *pollData = calloc(NUM_CANDIDATES * 3, sizeof(unsigned int));

    rewind(filePointer);

    for (int i = 0; i < lineCount; i++) {

        /* Using getc() to advance the input stream, skipping newline characters, so they aren't picked up by fgets().
        If the character read by getc() isn't a newline the action is undone via ungetc(). */

        if ((*newlineSkip = getc(filePointer)) != '\n') {
            ungetc(*newlineSkip ,filePointer);
        }

        fgets (stringBuffer, 7, filePointer);

        lengthCheck = strlen(stringBuffer);
        if (lengthCheck != 6) {
            printf("Line %d: The entry's length is invalid, skipping it...\n", i + 1);
            continue;
        }

        sscanf (stringBuffer,"0x%lx", &hexBuffer);
        bitStorage = hexBin(&hexBuffer);

        // Checking if voter age is within allowed range
        age = binDec (&bitStorage[0], 7);
        if (age < 18 | age > 99) {
            printf("Line %d: Voter age outside of allowed range, entry will not be accounted for.\n", i + 1);
            continue;
        }

        // Checking if voter gender is valid
        gender = binDec (&bitStorage[7], 2);
        if (gender < 1 | gender > 3) {
            printf("Line %d: Invalid value for voter gender, entry will not be accounted for.\n", i + 1);
            continue;
        }

        // Checking if vote is within the 1 candidate limit
        temp = 0;
        int votedFor = -1;
        for (int j = 9; j < 16; j++) {
            if (bitStorage[j] && temp == 0) {
                votedFor = (j - 9);
                temp++;
            }
            else if (bitStorage[j]) {
                printf("Line %d: Candidate limit violated, entry will not be accounted for.\n", i + 1);
                votedFor = -1;
                break;
            }
        }
        if (votedFor != -1) {
            int offset = 0;
            switch (gender) {

                default: break;

                case 2: offset = 1;
                break;

                case 3: offset = 2;
                break;
            }
            pollData[(votedFor * 3) + offset] += 1;
        }
        free (bitStorage);
    }

    int max = (pollData[0] + pollData[1] + pollData[2]);

    for (int i = 3; i < 21; i = i + 3) {
        temp = pollData[i] + pollData[i+1] + pollData[i+2];
        if (temp > max) {
            max = temp;
        }
    }

    free (newlineSkip);

    free (stringBuffer);

    free(pollData);

    fclose (filePointer);

    return (EXIT_SUCCESS);
}



