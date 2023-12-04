#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    // Setting up the 'numbers' array
    const char *NUMBERS[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    const int LEN_NUMBERS = sizeof(NUMBERS)/sizeof(NUMBERS[0]);
    
    // Preparing to open the file from command-line
    FILE *pF = fopen(argv[1], "r");
    char buf[256];

    if (pF == NULL) {
        printf("Can't open file\n");
        return -1;
    }
    
    // Assuming file can be opened now
    unsigned long calibration = 0;
    char *head;
    
    // Reading the file line by line
    while (fgets(buf, 255, pF) != NULL) {
        int firstDigit = 0;
        int lastDigit = 0;
        int firstDigitFound = 0;
       
        for (int j = 0; buf[j] != '\0'; j++) {
            if (isdigit(buf[j])) {
                int digit = (int)(buf[j] - '0');
                // 
                if (!firstDigitFound) {
                    firstDigit = digit;
                    lastDigit = firstDigit;

                    // Marking that the first digit has been found
                    firstDigitFound = 1;
                }
                else {
                    // Incrementing last digit if a digit is found
                    // and the first one has already been allocated
                    lastDigit = digit;
                }
            }
            else {
                // if character isn't digit, 
                int position = 0;
                // Iterating through the possible word numbers
                for (int k = 0; k < LEN_NUMBERS; k++) {
                    // See if the current NUMBER appears in our substring
                    head = strstr(buf + j, NUMBERS[k]);
                    // Get its position
                    position = head - (buf + j);
                    // Only process IF there's a match AND it's at the beginning
                    // of the string. That is, 'eightwothree' might match on 'two'
                    // first, which isn't what we want.
                    if (head != NULL && position == 0) {
                        // Checking if it's the first digit or not
                        if (!firstDigitFound) {
                            // NUMBERS[0] = 'one', NUMBERS[1] = 'two',
                            // So index + 1 will give us the integer value
                            // we want
                            firstDigit = k + 1;
                            lastDigit = firstDigit;

                            // Marking that the first digit has been found
                            firstDigitFound = 1;
                        } 
                        else {
                            lastDigit = k + 1;
                        }
                        // The -2 is because let's say we have a string that's
                        // 'eightwo' and we've found 'eight'.
                        // If we increment j by strlen('eight'), the for-loop with
                        // j as the index will j++, so instead of incrementing to 
                        // 'wo', it'll take us 'o'. Thus, we -1
                        //
                        // On top of that, we want to increment so we're left with ''two'
                        // because 'two' is a valid NUMBER value. Otherwise, 'eightwo' would
                        // get mistaken for 88 instead of 82. Hence, another -1.
                        j += strlen(NUMBERS[k]) - 2;
                        // We also want end this loop too
                        k = LEN_NUMBERS;
                    }
                }
            }
        }
        // Now that we've established the first and last digits, let's
        // fix the calibration value
        calibration += firstDigit * 10 + lastDigit;
    }

    printf("[!] Calibration value: %lu\n", calibration);
    fclose(pF);

    return 0;
}
