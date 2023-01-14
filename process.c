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
    element of the array.

    The same method is used for the array containing the age data, although there are 4 "columns" for the respective age
    ranges. */

    unsigned long hexBuffer;
    int gender, age, temp, offset, fatalError = 1;
    size_t lengthCheck;
    unsigned short* bitStorage = NULL;

    char *stringBuffer = calloc (7, sizeof (char));
    int *newlineSkip = (int*) malloc (sizeof (char));
    int *pollData = calloc (NUM_CANDIDATES * 3, sizeof (unsigned int));
    int *ageData = calloc (NUM_CANDIDATES * 4, sizeof (int));

    rewind(filePointer);

    for (int i = 0; i < lineCount; i++) {

        /* Resetting the error flag triggered by an invalid entry, meaning there's an entry following the invalid one,
        indicated by the fact the programme re-entered the for loop. */
        fatalError = 0;

        /* Using getc() to advance the input stream, skipping newline characters, so they aren't picked up by fgets().
        If the character read by getc() isn't a newline the action is undone via ungetc(). */

        if ((*newlineSkip = getc(filePointer)) != '\n') {
            ungetc(*newlineSkip ,filePointer);
        }

        fgets (stringBuffer, 7, filePointer);

        // Checking if the entry is 6 characters long (the 16-bit hex number + the "0x" prefix, quotes not included).
        lengthCheck = strlen(stringBuffer);
        if (lengthCheck != 6) {
            printf("Line %d: The entry's length is invalid, skipping it...\n", i + 1);
            putchar('\n');
            continue;
        }

        sscanf (stringBuffer,"0x%lx", &hexBuffer);
        bitStorage = hexBin(&hexBuffer);

        // Checking if voter age is within allowed range
        age = binDec (&bitStorage[0], 7);
        if (age < 18 | age > 99) {
            printf("Line %d: Voter age outside of allowed range, entry will not be accounted for.\n", i + 1);
            putchar('\n');
            continue;
        }

        // Checking if voter gender is valid
        gender = binDec (&bitStorage[7], 2);
        if (gender < 1 | gender > 3) {
            printf("Line %d: Invalid value for voter gender, entry will not be accounted for.\n", i + 1);
            putchar('\n');
            fatalError = 1;
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
                putchar('\n');
                votedFor = -1;
                break;
            }
        }

        // Initializing the array position offset to properly store the vote based on the voter's gender
        if (votedFor != -1) {
            offset = 0;
            switch (gender) {

                case 2: offset = 1;
                break;

                case 3: offset = 2;
                break;

                default: break;
            }
            pollData[(votedFor * 3) + offset] += 1;

            switch (age) {

                case 18 ... 29: ageData[(votedFor * 4)]++;
                break;

                case 30 ... 44: ageData[(votedFor * 3) + 1]++;
                break;

                case 45 ... 59: ageData[(votedFor * 3) + 2]++;
                break;

                default: ageData[(votedFor * 3) + 3]++;
                break;
            }
        }
        free (bitStorage);
    }

    free (stringBuffer);

    free (newlineSkip);

    /* If there are no more entries after an invalid one, the programme exits so the rest of the code isn't ran with
    non-existent "proper values" */
    if (fatalError == 1) {
        exit(EXIT_FAILURE);
    }

    // Determining which candidate got the most total votes
    int max = (pollData[0] + pollData[1] + pollData[2]);
    int maxPos = 0;

    for (int i = 3; i < 21; i += 3) {
        temp = pollData[i] + pollData[i+1] + pollData[i+2];
        if (temp > max) {
            max = temp;
            maxPos = i;
        }
    }

    puts("===========================| Poll Winner |===========================");
    putchar('\n');

    printf("Candidate #%d was voted for the most with %d vote(s) tallied up in their ballot.\n", 6 - ((maxPos - offset) / 3), max);
    putchar('\n');

    puts("========================| Gender Statistics |========================");
    putchar('\n');

    // Determining which candidate got voted for the most by each gender;
    for (offset = 0; offset < 3; offset++) {

        maxPos = 0;
        max = pollData[offset];

        for (int i = (3 + offset); i < (21 - offset); i += 3) {
            temp = pollData[i];
            if (temp > max) {
                max = temp;
                maxPos = i;
            }
        }

        if (offset == 0) {
            printf("Candidate #%d was voted for the most by men, with %d vote(s).\n", 6 - ((maxPos - offset) / 3), max);
            putchar('\n');
        }
        else if (offset == 1) {
            printf("Candidate #%d was voted for the most by women, with %d vote(s).\n", 6 - ((maxPos - offset) / 3), max);
            putchar('\n');
        }
        else {
            printf("Candidate #%d was voted for the most by other genders, with %d vote(s).\n", 6 - ((maxPos - offset) / 3), max);
            putchar('\n');
        }
    }

    puts("=========================| Age Information |=========================");
    putchar('\n');

    // Determining the number of voters in each age group;
    for (offset = 0; offset < 4; offset++) {

        temp = 0;

        for (int i = offset; i < (28 - offset); i+= 4){
            temp += ageData[i];
        }

        if (offset == 0) {
            printf("%d voter(s) were between the ages of 18 and 29.\n", temp);
            putchar('\n');
        }
        else if (offset == 1) {
            printf("%d voter(s) were between the ages of 30 and 44.\n", temp);
            putchar('\n');
        }
        else if (offset == 2) {
            printf("%d voter(s) were between the ages of 45 and 59.\n", temp);
            putchar('\n');
        }
        else {
            printf("%d voter(s) were over the age of 60.\n", temp);
            putchar('\n');
        }
    }

    puts("==========================| Miscellaneous |==========================");
    putchar('\n');

    /* Determining which candidate got voted for the most by "the youth" and which by the "elderly" (definition of youth
    for our case is anyone within the age range of 18 - 29. the rest are considered "elderly"). */
    for (offset = 0; offset < 2; offset++) {

        temp = 0;
        maxPos = 0;

        if (offset == 0) {
            max = ageData[0];
        }
        else {
            max = ageData[1] + ageData[2] + ageData[3];
        }

        for (int i = (4 + offset); i < (28 - offset); i += 4) {

            if (offset == 0) {
                temp = ageData[i];
            }
            else {
                temp = ageData[i] + ageData[i + 1] + ageData[i + 2];
            }

            if (temp > max) {
                max = temp;
                maxPos = i;
            }
        }

        if (offset == 0) {
            printf("#%d Candidate was voted for the most by the \"youth\", with %d votes.\n", 6 - ((maxPos - offset) / 4), max);
            putchar('\n');
        }
        else {
            printf("#%d Candidate was voted for the most by the \"elderly\", with %d votes.\n", 6 - ((maxPos - offset) / 4), max);
            putchar('\n');
        }
    }

    puts("====================| Candidate Vote Histograms |====================");

    /* Creating histograms for the votes received on a per-candidate basis, both total and per gender. If a candidate
    has received no votes from a gender, a histogram won't appear for said gender. */

    for (int i = 0; i < 21; i += 3) {

        putchar('\n');
        printf("Candidate #%d:\n", 6 - (i / 3));

        /* Traversing through each candidate's "column" in pollData and printing an "*" for each vote received. This
        process is repeated 3 times for each candidate since there are 3 gender values to tally up votes from, each with
        their respective column. */

        for (int j = i; j < (i + 3); j++) {

            if ((j - i) == 0) {
                for (int k = 0; k < pollData[j]; k++) {

                    if (k == 0) {
                        putchar('\n');
                        printf("    Men:   ");
                    }
                    printf("*");
                }
            }
            else if((j - i) == 1) {
                for (int k = 0; k < pollData[j]; k++) {

                    if (k == 0) {
                        putchar('\n');
                        printf("    Women: ");
                    }
                    printf("*");
                }
            }
            else {
                for (int k = 0; k < pollData[j]; k++) {

                    if (k == 0) {
                        putchar('\n');
                        printf("    Other: ");
                    }
                    printf("*");
                }
            }

        }
        putchar('\n');
    }

    puts("=====================================================================");
    putchar('\n');

    free(pollData);

    free (ageData);

    fclose (filePointer);

    printf("Execution finished, press ENTER to exit...\n");
    getchar();

    return (EXIT_SUCCESS);
}



