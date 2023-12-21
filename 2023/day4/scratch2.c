#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 256

int countNumbers(char *);
int *setNumArrByDelim(int, char *, char *);

int main(int argc, const char *argv[]) {
  FILE *pF = fopen(argv[1], "r");

  if (pF == NULL) {
    printf("Can't open file\n");
    return -1;
  }

  // Assuming file can be opened, count how many lines we have
  // (i.e., how many card we have)
  char buf[BUF];
  int numOfLines = 0;

  // Get the number of lines
  while (fgets(buf, BUF - 1, pF) != NULL) {
    numOfLines++;
  }

  // Setting up an integer array (card[0] = Card 1, etc)
  int *card = (int *)malloc(numOfLines * sizeof(int));
  
  // Initialize all values to 1 (because we have at least 1 of every card)
  for (int i = 0; i < numOfLines; i++) {
    card[i] = 1;  
  }

  // Resetting the file pointer to the beginning to read again
  rewind(pF);

  unsigned long score = 0;
  // There will always be at least one score card
  unsigned long scoreCardCount = 1;

  int cardNumber = 0;
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
          // Increment the score to track how many winning numbers we have
          score++;
        }
      }
    }

    // +1 to every subsequent card after this one
    // e.g., if card[0] has 4 winning numbers,
    // add 1 to card[1], card[2], card[3] and card[4]
    for (int m = 1; m <= score && (cardNumber + m) < numOfLines; m++) {
      // This inner loop is to account for every copy of the card
      // e.g., if card[1] = 3, then for every subsequent winning card,
      // it will count them three times.
      for (int n = 0; n < card[cardNumber]; n++) {
        card[cardNumber + m]++;
      }
    }

    // Increment card number
    cardNumber++;
    // Accumulate the number of cards we have
    scoreCardCount += card[cardNumber];
    // Reset score for next card
    score = 0;
    // Free the token
    free(token);
  }

  // Tidy up
  free(winningNumbers);
  free(scratchCard);
  free(card);
  fclose(pF);

  // Print final score
  printf("[!] Final score: %lu\n", scoreCardCount);

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
