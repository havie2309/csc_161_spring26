#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int roll_dice(){
    return rand() % 6 + 1;
}

void user_keep(int dice[5]){
    int valid_choice[5];
    bool valid = false;
    int input;

    // Ask until the user enter exactly 5 valid input
    while (!valid) {
        valid = true;
        printf("\nChoose dice to keep (0. Reroll, 1. Keep)\n");
        printf("Example: 1 1 0 0 1\n");
        printf("Enter your choice: "); 

        // Read the input and check if that is valid input
        for (int i = 0; i < 5; i++){
            if (scanf("%d", &valid_choice[i]) != 1){
                valid = false;
                break;
            }
        }

        // Clear invalid input if scanf failed
        if (!valid) {
            while (getchar() != '\n');
            printf("Invalid input. Enter only 5 numbers, only 0 or 1\n");
            continue;
        }
        input = getchar();

        // Check for extra characters after the 5 inputs
        if (input != '\n') {
            valid = false;
            // Clear the remainiing of the input 
            while (input != '\n') {
                input = getchar();
            }
        }

        // Check if all inputs are valid
        for (int i = 0; i < 5; i++){
            if (valid_choice[i] != 0 && valid_choice[i] != 1) {
                valid = false;
            }
        }

        // Print error message if the input is invalid
        if (!valid) {
            printf("Invalid input. Enter only 5 numbers, only 0 or 1\n");
        }
    }

    // Mark dice to reroll by setting them to 0
    for (int i = 0; i < 5; i++){
        if (valid_choice[i] == 0){
            dice[i] = 0;
        }
    }
}

void user_score_store(int dice[5], int score_lines[6]){
    int store; 
    int sum = 0;
    bool valid = false;
    int input;
    // Ask until the user chooses a valid bin
    while (!valid){
        valid = true;
        printf("Where you want to store your score?\nBin 1\nBin 2\nBin 3\nBin 4\nBin 5\nBin 6\nEnter your choice (1-6): ");
        // Read the user input and check if it is valid
        if (scanf("%d", &store) != 1) {
            valid = false;
            // Clear invalid input if it wrong
            while (getchar() != '\n');
            printf("Invalid input. Enter a number from 1 to 6.\n");
            continue;
        }
        input = getchar();
        // Check for extra characters after the valid input
        if (input != '\n') {
            valid = false;
            // Clear the remainiing of the input 
            while (input != '\n') {
                input = getchar();
            }
            printf("Invalid input. Enter only one number from 1 to 6.\n");
            continue;
        }
        // Check that the bin number is in range
        if (store < 1 || store > 6) {
            printf("Choice must be in 1 to 6.\n");
            valid = false;
            continue;
        }
        // Check that the line has not already been stored
        if (score_lines[store - 1] != -1){
            printf("Oops! You have already stored this line.\n");
            valid = true;
            continue;
        } 
    }
    // Calculate the score for the selected line
    for (int i = 0; i < 5; i++){
        if (dice[i] == store){
            sum += dice[i];
        }
    }
    score_lines[store-1] = sum;
    printf("Stored %d points in line %d.\n", sum, store);
}
    
int main(){
    int dice[5];
    int score_lines[6];
    int game = 1;
    printf("\nWelcome to Yahtzee!\n");
    srand(time(NULL));

    // Initialize all score lines as unused
    for (int i = 0; i < 6; i++){
        score_lines[i] = -1;
    } 

    // Play 6 rounds of one game
    do {
        int turn = 1;
        printf("\nGAME %d\n", game);
        printf("Rolling dices...\n");
        printf("You rolled: ");

        // Roll all 5 dice at the start of the round
        for (int i = 0; i < 5; i++){
            dice[i] = roll_dice();
            printf("%d ", dice[i]);
        }

        // User can reroll 2 times
        do {
            user_keep(dice);
            // Reroll dice marked as 0
            for (int i = 0; i < 5; i++){
                if (dice[i] == 0){
                    dice[i] = roll_dice();
                }
            }

            // Print the updated dice
            printf("\nNew dice: ");
            for (int i = 0; i < 5; i++){
                printf("%d ", dice[i]);
            }
            turn++;
        } while (turn < 3);

        user_score_store(dice, score_lines);
        game++; 
    } while (game < 7);

    // Replace unused lines with 0
    for (int i = 0; i < 6; i++){
        if (score_lines[i] == -1){
            score_lines[i] = 0;
        }
    }

    int total = 0; 
    
    // Print the score in each line
    for (int i = 0; i < 6; i++){
        printf("Bin %d: %d\n", i + 1, score_lines[i]);
    }

    // Calculate the total score
    for (int i = 0; i < 6; i++){
        total += score_lines[i];
    }
    printf("Your total score is %d\n", total);
}