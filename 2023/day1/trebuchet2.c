#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, const char *argv[]) {
    FILE *pF = fopen(argv[1], "r");
    char buf[256];

    if (pF == NULL) {
        printf("Can't open file\n");
        return -1;
    }
    
    // Assuming file can be opened now
    unsigned long calibration = 0;
    
    while (fgets(buf, 255, pF) != NULL) {
        int firstDigit = 0;
        int lastDigit = 0;
        int firstDigitFound = 0;

        for (int j = 0; buf[j] != '\0'; j++) {
            if (isdigit(buf[j])) {
                int digit = (int)(buf[j] - '0');
                // e.g., '3' is stored as ASCII code 51
                // '0' is stored as ASCII code 48
                // Thus if we want to convert '3' to 3,
                // just do '3' - '0', and then cast as int
                if (firstDigitFound == 0) {
                    firstDigit = digit;
                    lastDigit = firstDigit;

                    // Marking that the first digit is found
                    firstDigitFound = 1;
                }
                else {
                    // If we encounter another digit, set lastDigit to it
                    lastDigit = digit;
                }
            }
        }
        // e.g., firstDigit = 1, lastDigit = 2, then value to add to calibration
        // is 12
        calibration += (firstDigit * 10) + lastDigit;
    }
    printf("[!] Calibration value: %lu\n", calibration);

    fclose(pF);

    return 0;
}
