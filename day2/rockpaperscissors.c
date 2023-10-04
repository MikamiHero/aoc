#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int choiceScore(char choice) {
    // X = rock, Y = paper, Z = scissors
    // (Rock = 1, Paper = 2, Scissors = 3)
    int score = 0;

    switch(choice) {
        case 'X':
            score = 1;
            break;
        case 'Y':
            score = 2;
            break;
        case 'Z':
            score = 3;
            break;
        default:
            score = 0;
    }

    return score;
}

int winOrLose(char op, char pl) {
    // Player: X = rock, Y = paper, Z = scissors
    // Opponent: A = rock, B = paper, C = scissors
    int score = 0;

    // if opponent picks rock
    if (op == 'A') {
        if (pl == 'X') {
            score = 3;
        }
        else if (pl == 'Y') {
            score = 6;
        }
        else if (pl == 'Z') {
            score = 0;
        }
    }
    // if opponent picks paper
    else if (op == 'B') {
        if (pl == 'X') {
            score = 0;
        }
        else if (pl == 'Y') {
            score = 3;
        }
        else if (pl == 'Z') {
            score = 6;
        }
    }
    // if opponent picks scissors
    else if (op == 'C') {
        if (pl == 'X') {
            score = 6;
        }
        else if (pl == 'Y') {
            score = 0;
        }
        else if (pl == 'Z') {
            score = 3;
        }
    }

    return score;
}

int main() {
    FILE *pF = fopen("input", "r");
    char buffer[255];
    char opponent, player = 0;
    int roundPoints, totalPoints = 0;

    // Checking for file existence
    if (pF == NULL) {
        printf("Unable to open file!\n");
    } 
    else {
        while(fgets(buffer, 255, pF) != NULL) {
            // First character is opponent
            // second character is whitespace
            // third character is player
            opponent = buffer[0];
            player = buffer[2];

            // First, determine player score from choice
            roundPoints = choiceScore(player);

            // Next, determine if player won or not
            roundPoints += winOrLose(opponent, player);

            // Add to total
            totalPoints += roundPoints;
        }
        printf("The final score: %d\n", totalPoints);
    }
    return 0;
}
