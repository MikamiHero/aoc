#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, const char* argv[]) {
    FILE *pF = fopen(argv[1], "r");
    char buffer[255];

    // Checking for file existence
    if (pF == NULL) {
        printf("Unable to open file!\n");
    }
    else {
        int priority = 0;
        while(fgets(buffer, 255, pF) != NULL) {
            // Declaring some variables we'll need
            int length, halfLength = 0;

            // First, we'll store the length of the line
            // (-1 because of '\0')
            length = strlen(buffer) - 1;

            // Next, we'll split the line in two
            // to represent the two compartments for the rucksack
            // (thankfully, we know they're all even)
            halfLength = length / 2;
            
            char* firstCompartment = malloc(halfLength + 1); // +1 for '\0'
            memcpy(firstCompartment, buffer, halfLength);
            firstCompartment[halfLength] = '\0';

            char* secondCompartment = malloc(halfLength + 1); // +1 for '\0'
            memcpy(secondCompartment, buffer+halfLength, halfLength); // didn't realise that you could go (buffer + int) to index a substring...
            secondCompartment[halfLength] = '\0';

            printf("s1: %s, s2: %s\n", firstCompartment, secondCompartment);
            
            // The problem constraints tell us that only *one* character will be common between both strings. So we'll do a naive search
            for (int j = 0; j < halfLength; j++) {
                char x = firstCompartment[j];
                int matchFound = 0;
                if (strchr(secondCompartment, x) != NULL) {
                    printf("Found a match: %c\n", x);
                    printf("Value of match: %d\n", x);
                    // If character is lowercase, subtract 96
                    // If character is uppercase, subtract 38
                    // a to z are in [1, 26]; A to Z are in [27, 52]
                    // ASCII 'a' = 97; ASCII 'A' = 65
                    // Then add to priority
                    priority += (isupper(x)) ? (x - 38) : (x - 96);
                    break;
                }
            }
        }
        
        // Finally, print the final priority value
        printf("[+] Priority value: %d\n", priority);
    }
    return 0;
}
