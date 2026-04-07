#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#define ROCK 0
#define PAPER 1
#define SCISSORS 2


// returns rock, paper, or scissors randomly
int computer_chooser_rps() {
  int value = rand() % 3;

  //if value = 0 it will return rock, if 1 it will return paper, else return scissors
  if (value == SCISSORS) {
      return SCISSORS;
    } else if (value == ROCK) {
      return ROCK;
    } else {
      return PAPER;
    }
}

int user_choose_rps(){
  int user_choice;
  int num_values_read;

//do while loop that runs for as along as user does not input valid input of 1. 2. or 3
  do {
    // Show a prompt message
    printf("What move do you want to play?\n1. Rock\n2. Paper\n3. Scissors \nEnter the number of your choice: ");

    // Use scanf to read in an integer
    int num_values_read = scanf("%d", &user_choice);

    // Clear any remaining input from the user
    while (getchar() != '\n') {}

    // Print message letting user know if valid char was inputted
    if (user_choice != 1) {
      printf("Invalid choice. Please type a valid input of 1 or 2 or 3\n");
    } else {
      printf("Valid input. Good job!!!\n");
    }
    
  } while (!(user_choice == 1 || user_choice == 2 || user_choice == 3));



  //return user choice
  if (user_choice == 1) {
    return ROCK;
  } else if (user_choice == 2) {
    return PAPER;
  } else {
    return SCISSORS;
  }
}

//check if there is a tie
bool is_tie(int move1, int move2){
  if(move1==move2){
    return true;
  } else {
    return false;
  }
}

//check if user wins
bool is_win(int move1, int move2){
  if ((move1 == SCISSORS && move2 == ROCK) || (move1 == ROCK && move2 == PAPER) || (move1 == PAPER && move2 == SCISSORS)){
    return true;
  } else {
    return false;
  }
}

int user_prompt_again(){
   int value;

  //do while loop that runs for as long as user does not input valid input of 1 or 2
  do {
    // Show a prompt message
    printf("Do you want to play again?\n1. Yes\n2. No: ");

    // Use scanf to read in an integer
    int num_values_read = scanf("%d", &value);

    // Clear any remaining input from the user
    while (getchar() != '\n') {}

    // Print the value, if there was one
    if (num_values_read != 1) {
      printf("You typed %d. Please type a valid input of 1 or 2\n", value);
    } else {
      printf("Valid input. Good job!!!\n");
    }
  } while (!(value == 1 || value == 2));

  if (value == 1){
      return true;
    } else {
      return false;
    }

}

//prints user choice
void print_choice(int choice){
  if(choice==ROCK){
    printf("ROCK");
  } else if (choice==SCISSORS){
    printf("SCISSORS");
  } else {
    printf("PAPER");
  }
}

int main() {
  int wins = 0;
  int losses = 0;
  int ties = 0;

  //do while loop that plays again if the user chooses yes!
  do {

  // Set the random seed to the current time in seconds
    srand(time(NULL));

    int value = computer_chooser_rps();
    // Use scanf to read in an integer
    int v = user_choose_rps();
    
    printf("You chose ");
    print_choice(v);
    printf(".\n");

    printf("The computer chose ");
    print_choice(value);
    printf(".\n");

    if (is_win(value, v)){
      printf("You win!\n");
      wins+=1;
    } else if (is_tie(value, v)) {
      printf("It's a tie!\n");
      ties+=1;
    } else {
      printf("You loss!\n");
      losses+=1;
    }
    printf("Wins: %d\nTies: %d\nLosses: %d\n", wins ,ties ,losses);
  } while (user_prompt_again());
}

