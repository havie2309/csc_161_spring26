#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define BOARD_SIZE 42
#define INPUT_LENGTH 4

// Constants to print in bold red text, bold yellow text, and to reset text style
#define START_RED "\033[1m\033[31m"
#define START_YELLOW "\033[1m\033[33m"
#define RESET_COLOR "\033[0m"

// Prints the current board with column labels and colored tokens
void print_board(char board[]){
  for (int col = 0; col < BOARD_WIDTH; col++){
    printf("  %c ", col + 'A');
  }
  printf("\n");
  // Go through each row and column 
  for (int row = 0; row < BOARD_HEIGHT; row++){
    printf("|");
    for (int col = 0; col < BOARD_WIDTH; col++){
      // If the cell has yellow token print in yellow, otherwise red 
      if (board[row * BOARD_WIDTH + col] == 'Y'){
        printf(START_YELLOW);
      } else if (board[row * BOARD_WIDTH + col] == 'R'){
        printf(START_RED);
      }
      printf(" %c ", board[row * BOARD_WIDTH + col]);
      printf(RESET_COLOR "|");
    }
    printf("\n");
  }
  printf("_____________________________\n\n");
}

// Ask player to choose a valid column and returns the valid column 
int get_move(char board[], char turn){
  print_board(board);
  char input[INPUT_LENGTH];
  char *fgets_output;
  do {
    printf("Choose a column (A-G) to drop %c token: ", turn);
    fgets_output = fgets(input, INPUT_LENGTH, stdin);
    // Exit the program if fgets fails to read input
    if (fgets_output == NULL) {
      fprintf(stderr, "Failed to read input from user.\n");
      exit(EXIT_FAILURE);
    }
    // Reject letters outside A-G 
    if (input[0] < 'A' || input[0] > 'G'){
      printf("Invalid input. Please enter A-G.\n");
    // Reject valid column that has no empty space left
    } else if (board[input[0] - 'A'] != ' '){
      printf("This column is full.\n");
    // Reject more than one character
    } else if (input[1] != '\n' && input[1] != '\0'){
      printf("Invalid input. Please just enter one character.\n");
    // Valid input
    } else {
      int col = input[0] - 'A';
      return col;
    }
  } while (1);
}

// Drops token into the choosen column and returns its row 
int drop_token(char board[], int col, char turn){
  for (int row = BOARD_HEIGHT - 1; row >= 0; row--){
    int i = row * BOARD_WIDTH + col;
    if (board[i] == ' '){
      board[i] = turn;
      return row;
    }
  }
  return 0;
}

// Returns true if the last move at created four in a row (win game)
bool is_win(char board[], int row, int col, char turn){
  int current_col;
  int current_row;
  int count;

  // Win in horizontal
  // Count tokens have same turn in the direction of the left and right of the token
  count = 1;
  current_col = col - 1;
  while (current_col >= 0 && board[row * BOARD_WIDTH + current_col] == turn){
    count++;
    current_col--;
  }
  current_col = col + 1;
  while (current_col < BOARD_WIDTH && board[row * BOARD_WIDTH + current_col] == turn){
    count++;
    current_col++;
  }
  if (count >= 4) return true;

  // Win in vertical
  // Count tokens have same turn in the direction of above and below the token
  count = 1;
  current_row = row - 1;
  while (current_row >= 0 && board[current_row * BOARD_WIDTH + col] == turn){
    count++;
    current_row--;
  }
  current_row = row + 1;
  while (current_row < BOARD_HEIGHT && board[current_row * BOARD_WIDTH + col] == turn){
    count++;
    current_row++;
  }
  if (count >= 4) return true;

  // Win in diagonal top-left to bottom-right ( \ )
  // Count tokens have same turn in the direction of the up-left and down-right from the token
  count = 1;
  current_col = col - 1;
  current_row = row - 1;
  while (current_col >= 0 && current_row >= 0 && board[current_row * BOARD_WIDTH + current_col] == turn){
    count++;
    current_col--;
    current_row--;
  }
  current_col = col + 1;
  current_row = row + 1;
  while (current_col < BOARD_WIDTH && current_row < BOARD_HEIGHT && board[current_row * BOARD_WIDTH + current_col] == turn){
    count++;
    current_col++;
    current_row++;
  }
  if (count >= 4) return true;

  // Win in diagonal top-right to bottom-left ( / )
  // Count tokens have same turn in the direction of the down-left and up-right from the token
  count = 1;
  current_col = col - 1;
  current_row = row + 1;
  while (current_col >= 0 && current_row < BOARD_HEIGHT && board[current_row * BOARD_WIDTH + current_col] == turn){
    count++;
    current_col--;
    current_row++;
  }
  current_col = col + 1;
  current_row = row - 1;
  while (current_col < BOARD_WIDTH && current_row >= 0 && board[current_row * BOARD_WIDTH + current_col] == turn){
    count++;
    current_col++;
    current_row--;
  }
  if (count >= 4) return true;

  return false;
}

// Returns true if all columns are full and no more moves can be made
bool is_tie(char board[]){
  for (int col = 0; col < BOARD_WIDTH; col++){
    if (board[col] == ' '){
      return false;
    }
  }
  return true;
}

int main(){
  // Initialize the board with empty spaces and start with player Y
  char board[BOARD_SIZE];
  char current_turn = 'Y';
  memset(board, ' ', BOARD_SIZE);
  while (1) {
    printf("It's player %c's turn.\n", current_turn);
    // Get valid column from the current player and drop the token
    int col = get_move(board, current_turn);
    int row = drop_token(board, col, current_turn);
    // Check if the current player won after their move
    if (is_win(board, row, col, current_turn)){
      print_board(board);
      printf("Congratulations!!! Player %d wins!\n", (current_turn == 'Y') ? 1 : 2);
      break;
    }
    // Check if the board is full with no winner
    if (is_tie(board)){
      print_board(board);
      printf("Oops! All the columns are full. Tie!\n");
      break;
    }
    // Switch to the other player in  next turn
    current_turn = (current_turn == 'Y') ? 'R' : 'Y';
  }
  return 0;
}
