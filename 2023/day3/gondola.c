#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // Get the number of lines
    while (fgets(buf, BUF, pF) != NULL) {
        // We only want to set this once
        if (numOfLines == 0) {
            lineLength = strlen(buf);
        }
        numOfLines++;
    }

    // Resetting the file pointer to the beginning to read again
    rewind(pF);

    // Setting up a 2D array where
    // rows = numOfLines; columns = lineLength - 1 (ignoring '\0')
    char *arr[numOfLines];
    for (int i = 0; i < numOfLines; i++) {
        arr[i] = (char*)malloc((lineLength - 1) * sizeof(char));
    }


    // Reading the file again but this actually propagate data
    char *allowedSymbols = "$+*#@%-=";
    int x = 0;
    while (fgets(buf, BUF, pF) != NULL) {
        for (int y = 0; buf[y] != '\0'; y++) {
            arr[x][y] = buf[y];
        }
        x++;
    }

    // Going through the 2D array now, looking for symbols
    // and handling cases where they're touching an integer
    int sum = 0;
    for (int j = 0; j < numOfLines; j++) {
        for (int k = 0; k < lineLength - 1; k++) {
            if (strchr(allowedSymbols, arr[j][k]) != NULL) {
                // If we get a symbol match, we want to look around it
                // for numbers, and if any are touching, add it to the
                // cumulative sum
                sum += searchAround(j, k, arr);
            }
        }
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
