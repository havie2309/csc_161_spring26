#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define INPUT_LENGTH 10

// Print the current game board
void print_board(char board[]) {
  printf(" %c | %c | %c \n---+---+---\n", board[0], board[1], board[2]);
  printf(" %c | %c | %c \n---+---+---\n", board[3], board[4], board[5]);
  printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

// Print board showing available moves
void print_choices(char board[]){
  char new_board[9];
  // Copy original board into new_board
  for (int i = 0; i < 9; i++){
    new_board[i] = board[i];
  }
  // Replace empty spaces with numbers from 1 to 9
  for (int i = 0; i < 9; i++){
    if (new_board[i] == ' '){
      new_board[i] = i+'1';
    }
  }
  printf(" %c | %c | %c \n---+---+---\n", new_board[0], new_board[1], new_board[2]);
  printf(" %c | %c | %c \n---+---+---\n", new_board[3], new_board[4], new_board[5]);
  printf(" %c | %c | %c \n", new_board[6], new_board[7], new_board[8]);
}

int get_move(char board[], char turn){
  print_choices(board);
  char input[INPUT_LENGTH];
  char *fgets_output;
  do {
    printf("Enter the number of the cell to place an %c: ", turn);
    fgets_output = fgets(input, INPUT_LENGTH, stdin);
    // Check if input failed
    if (fgets_output == NULL) {
      fprintf(stderr, "Failed to read input from user.\n");

    // Check if selected cell is unvailable
    } else if (board[atoi(input) -1] != ' ') {
      printf("This space is not empty.\n");
     // If the input is valid then return index
    } else {
        int value = atoi(input) - 1 ;
        return value;
    }
  } while (1);
}

// Check if there is a winner
bool check_win(char board[]) {
  // Check for horizontal
  for (int i = 0; i < 3; i++) {
    if (board[3*i] == 'X' && board[3*i + 1] == 'X' && board[3*i + 2] =='X') {
      return true;
    } else if (board[3*i] == 'O' && board[3*i + 1] == 'O' && board[3*i + 2] =='O') {
      return true;
    }
  }
  // Check for vertical
  for (int i = 0; i < 3; i++) {
    if (board[i] == 'X' && board[i+3] == 'X' && board[i+6] == 'X') {
      return true;
    } else if (board[i] == 'O' && board[i+3] == 'O' && board[i+6] == 'O') {
      return true;
    }
  }
  // Check for diagonal
  if (board[0] == 'X' && board[4] == 'X' && board[8] == 'X') {
    return true;
  } else if (board[2] == 'X' && board[4] == 'X' && board[6] == 'X') {
    return true;
  } else if (board[0] == 'O' && board[4] == 'O' && board[8] == 'O') {
    return true;
  } else if (board[2] == 'O' && board[4] == 'O' && board[6] == 'O') {
    return true;
  }
  return false;
}

// Check if the game is a tie
bool check_tie(char board[]) {
  // Check if any empty space still exists
  for (int i = 0; i < 9; i++) {
    // Still an empty space
    if (board[i] == ' ') {
      return false;
    }
  }
  // If no empty spaces and no winner return tie
  return !(check_win(board));
}

bool user_prompt(){
  char input[INPUT_LENGTH];
  char *fgets_output;

  // Keep asking until user enters Y or N
  do {
    printf("Do you want to play again? (Y/N)\nEnter answer: ");
    fgets_output = fgets(input, INPUT_LENGTH, stdin);
    if (fgets_output == NULL) {
    fprintf(stderr, "Failed to read input from user.\n");
    }
  } while (strcmp(input, "Y\n") != 0 && strcmp(input, "N\n") != 0);
  return (strcmp(input, "Y\n") == 0);
}

int main() {
  // TODO: Implement tic-tac-toe here
  char current_turn;
  char board[9];
  int game;
  
  // Loop to allow replaying the game
  do {
      current_turn = 'X';
      memset(board, ' ', 9);
      game = 1;

    // Main game loop 
    while (game < 10){
      print_board(board);
      printf("It's player %c's turn.\n", current_turn);
      int move = get_move(board, current_turn);
      board[move] = current_turn;

      // Check for tie
      if (check_tie(board)) {
        print_board(board);
        printf("The game is a tie.\n");
        break;

      // Check for winner
      } else if (check_win(board)) {
        print_board(board);
        printf("%c wins\n", current_turn);
        break;
      }

      // Switch player turn
      current_turn = (current_turn == 'X') ? 'O' : 'X';
      game++;
    } 
  } while (user_prompt());
}
