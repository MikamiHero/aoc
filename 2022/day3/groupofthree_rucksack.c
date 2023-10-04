#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN 52
#define BUF 255

int alphabetValue(char y) {
    return (isupper(y) ? (y - 38) : (y - 96));
}

int main(int argc, const char* argv[]) {
    FILE *pF = fopen(argv[1], "r");
    char buffer[BUF];

    // Checking for file existence
    if (pF == NULL) {
        printf("Unable to open file!\n");
    }
    else {
        int priority = 0, count = 0;
        int map1[LEN] = {0}, map2[LEN] = {0}, map3[LEN] = {0};
        while(fgets(buffer, BUF, pF) != NULL) {
            for (int j = 0; j < strlen(buffer) - 1; j++) {
                char x = buffer[j];
                switch(count) {
                    case(0):
                        // For each character found, +1 to frequency in its relevant position in the map/lookup
                        map1[alphabetValue(x) - 1]++;
                        break;
                    case(1):
                        map2[alphabetValue(x) - 1]++;
                        break;
                    case(2):
                        map3[alphabetValue(x) - 1]++;
                        break;
                    default:
                        break;

                }
            }
            count++;
            // This means we've read three lines
            if (count == 3) {
                for (int k = 0; k < LEN; k++) {
                    // If all three maps have a non-zero value for this index, it means this character appears in all three lines
                    if (map1[k] != 0 && map2[k] != 0 && map3[k] != 0) {
                        // Since array is 0-indexed (i.e., 'a' corresponds to 0), then the actual value to be added onto the priority is (k+1)
                        priority += k + 1;
                    }
                }
                // reset the count for the next group of three lines as well as the maps
                count = 0;
                memset(map1, 0, sizeof(map1));
                memset(map2, 0, sizeof(map2));
                memset(map3, 0, sizeof(map3));
            }
        }
        
        // Finally, print the final priority value
        printf("[+] Priority value: %d\n", priority);

        // Closing the file
        fclose(pF);
    }
    return 0;
}
