#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *pF = fopen("input", "r");
    char buffer[255];

    // Checking for file existence
    if (pF == NULL) {
        printf("Unable to open file!\n");
    } 
    else {
        int elfIndex = 1;
        int calorieCount = 0;
        int highestCalorieCount = 0;
        int highestCalorieElf = 1;
        
        // Reading the file in line by line
        while(fgets(buffer, 255, pF) != NULL) {
            if (buffer[0] == '\n') {
                // empty line means we've reached the end of the calorie listings
                // for that elf, so we check to see if it's carrying the most calories
                if (calorieCount > highestCalorieCount) {
                    highestCalorieCount = calorieCount;
                    highestCalorieElf = elfIndex;
                }

                // Reset the calorie count and increment which elf we're on
                calorieCount = 0;
                elfIndex++;
            }
            else {
                // if not empty line, add integer to running calorie count
                calorieCount += atoi(buffer);
            }
            printf("%s", buffer);
        }
        fclose(pF);
    
        printf("Elf #%d has the highest calorie count of %d\n", highestCalorieElf, highestCalorieCount);
    }


    return 0;
}
