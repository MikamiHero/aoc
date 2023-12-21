#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 256

int countNumbers(char *);
int *setNumArrByDelim(int, char *, char *);

int main(int argc, const char *argv[]) {
  FILE *pF = fopen(argv[1], "r");
  char buf[BUF];

  if (pF == NULL) {
    printf("Can't open file\n");
    return -1;
  }

  // Assuming file can be opened now
  unsigned long totalScore = 0;
  unsigned long scoreCard = 0;
  int *winningNumbers;
  int *scratchCard;

  while (fgets(buf, BUF - 1, pF) != NULL) {
    char *token;
    int tokenCount = 1;

    int winningNumbersLen = 0;
    int scratchCardLen = 0;

    // The first token will be "Card #", so we want to ignore it and keep
    // finding the rest
    token = strtok(buf, ":|");
    while (token != NULL) {
      if (tokenCount == 2) {
        // Token count == 2 ==> winning numbers
        winningNumbersLen = countNumbers(token);
        winningNumbers = setNumArrByDelim(winningNumbersLen, " \t\n", token);
      } else if (tokenCount == 3) {
        // Token count == 3 ==> scratch card
        scratchCardLen = countNumbers(token);
        scratchCard = setNumArrByDelim(scratchCardLen, " \t\n", token);
      }
      token = strtok(NULL, ":|");
      tokenCount++;
    }

    // Now that both arrays are propagated, let's do a naive search
    for (int j = 0; j < scratchCardLen; j++) {
      int scratchNum = scratchCard[j];
      // Looping through winning numbers to find a match
      for (int k = 0; k < winningNumbersLen; k++) {
        if (scratchNum == winningNumbers[k]) {
          // If score for the card is 0, set it 1. Else, double it
          scoreCard += scoreCard == 0 ? 1 : scoreCard;
        }
      }
    }

    // Add to total score
    totalScore += scoreCard;
    // Reset score for next card
    scoreCard = 0;
  }

  // Tidy up
  free(winningNumbers);
  free(scratchCard);
  fclose(pF);

  // Print final score
  printf("[!] Final score: %lu\n", totalScore);

  return 0;
}

/*
 * Separate a string of numbers by delimiter
 * @param int Length for array
 * @param *delim Delimiters to separate on
 * @param *str The string to
 *
 * @return A pointer to an array of the numbers (e.g., [41, 48, 83, 86, 17])
 *
 * e.g., setNumArrByDelim(5, " \t\n", "41 48 83 86 17") should return
 *       [41, 48, 83, 86, 17]
 */
int *setNumArrByDelim(int len, char *delim, char *str) {
  char *num;
  int idx = 0;

  int *arr = (int *)malloc(len * sizeof(int));
  while ((num = strsep(&str, delim)) != NULL) {
    if (*num == '\0') {
      continue;
    }
    arr[idx] = atoi(num);
    idx++;
  }
  return arr;
}

/*
 * Counts how many numbers appear in a whitespace
 * separated string.
 * @param char The string with numbers
 *
 * @return How many numbers it found in the string
 *
 * e.g., countNumbers("41 48 83 86 17") should return 5
 */
int countNumbers(char *str) {
  int count = 0;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (!isspace(str[i])) {
      while (i < len && !isspace(str[i])) {
        i++;
      }
      count++;
    }
  }
  return count;
}
