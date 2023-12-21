#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF 256

int charIsPeriod(char);
int searchAround(int, int, char *[]);

int main(int argc, const char *argv[]) {
    FILE *pF = fopen(argv[1], "r");

    if (pF == NULL) {
        printf("Can't open file\n");
        return -1;
    }

    // Assuming file can be opened
    char buf[BUF];
    int numOfLines = 0;
    int lineLength = 0;
    int grandSum = 0;

    // Get the number of lines
    while (fgets(buf, BUF, pF) != NULL) {
        // We only want to set this once
        if (numOfLines == 0) {
            lineLength = strlen(buf);
        }
        // For the current line, delimit on '.'
        char *delim = ".%+*#@%-=$";
        char *token;
        // Get the first token
        token = strtok(buf, delim);
        // Only add to the grand sum if it's a number
        grandSum += token != NULL ? atoi(token) : 0;

        // Walk to find the other tokens
        while (token != NULL) {
            token = strtok(NULL, delim);
            grandSum += token != NULL ? atoi(token) : 0;
        }
        numOfLines++;
    }

    printf("[!] Grand sum of all numbers: %d\n", grandSum);


    // Resetting the file pointer to the beginning to read again
    rewind(pF);

    // Setting up a 2D array where 
    // rows = # of lines; columns = line length - 1 (ignoring '\0')
    char *arr[numOfLines];
    for (int i = 0; i < numOfLines; i++) {
        arr[i] = (char*)malloc((lineLength - 1) * sizeof(char));
    }

    // Reading in the file again


    char *syms = "%+*#@%-=$";

    // Iterating through the 2D array, and for every number we encounter
    // look around its digits to see if there's a symbol in the list above.
    //
    // If there isn't any, deduct that value from the grand sum
    for (int j = 0; j < numOfLines; j++) {
        for (int k = 0; k < lineLength - 1; k++) {
            char x = arr[j][k];
            if (isdigit(x)) {
                printf("%c", x);
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }

    // Tidy up
    fclose(pF);

    return 0;
}

// Checks if character is '.'
int charIsPeriod(char c) {
    return c == '.' ? 1 : 0;
}

// Search the neighbouring array index for numbers
int searchAround(int x, int y, char *grid[]) {
    printf("[!] %c found at (%d,%d)\n", grid[x][y], x, y);
    return 0;
}
