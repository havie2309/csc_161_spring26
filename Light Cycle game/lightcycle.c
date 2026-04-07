#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

// You can adjust the frame rate to change the game speed. The demo runs at 4 frames per second.
#define FRAME_RATE 4
// Width and height 2 cell taller because I want to create a wall, the inside ground still 35x25
#define MAZE_WIDTH 37
#define MAZE_HEIGHT 27

/**
 * Sleep for a given number of milliseconds
 * \param   ms  The number of milliseconds to sleep for
 */
void sleep_ms(size_t ms) {
  struct timespec ts;
  size_t rem = ms % 1000;
  ts.tv_sec = (ms - rem) / 1000;
  ts.tv_nsec = rem * 1000000;

  // Sleep repeatedly as long as nanosleep is interrupted
  while (nanosleep(&ts, &ts) != 0) {}
}

void init_board(int maze[]){
  // Create maze with the wall outside the main ground
  for (int row = 0; row < MAZE_HEIGHT; row++) {
    for (int col = 0; col < MAZE_WIDTH; col++) {
      int index = row * MAZE_WIDTH + col;
      // Set which is the position of empty cell, which is a wall 
      if (row == 0 || row == MAZE_HEIGHT - 1 || col == 0 || col == MAZE_WIDTH - 1) {
          maze[index] = 1;
      } else {
        maze[index] = 0;
      }
    }
  }
}

// Print the mazee with wall, player 1 and player 2
void print_maze(int maze[]) {
  // TODO: Implement this function in part A
  for (int row = 0; row < MAZE_HEIGHT; row++){
    for (int col = 0; col < MAZE_WIDTH; col++){
      int index = row * MAZE_WIDTH + col;
      // If it is an empty cell, print with black
      if (maze[index] == 0) {
        attron(COLOR_PAIR(0));
        mvaddch(row, col * 2, ' ');
        mvaddch(row, col * 2 + 1, ' ');
        attroff(COLOR_PAIR(0));

      // If it is wall, draw the border
      } else if (maze[index] == 1) {
        mvaddch(row, col*2, ACS_CKBOARD);
        addch(ACS_CKBOARD);

      // If it is the player 1 (cell type 2), draw blue
      } else if (maze[index] == 2) {
        attron(COLOR_PAIR(1));
        mvaddch(row, col * 2, ' ');
        mvaddch(row, col * 2 + 1, ' ');
        attroff(COLOR_PAIR(1));

      // If it is the player 2 (cell type 3), draw yellow
      } else if (maze[index] == 3) {
        attron(COLOR_PAIR(2));
        mvaddch(row, col * 2, ' ');
        mvaddch(row, col * 2 + 1, ' ');
        attroff(COLOR_PAIR(2));
      }
    }
  }
}

// Print player base on position and color
void print_player(int x, int y, int color){
  attron(COLOR_PAIR(color));
  mvaddch(y, x * 2, ' ');
  mvaddch(y, x * 2 + 1, ' ');
  attroff(COLOR_PAIR(color));
}

// Movement direction of player
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} direction;

// Check if the next move is a 180-degree turn
bool reverse_turn(int current, int next) {
  // If it is a 180-degree turn immediately return true
    if (current == UP && next == DOWN) {
      return true;
    } if (current == DOWN && next == UP) {
      return true;
    } if (current == LEFT && next == RIGHT) {
      return true;
    } if (current == RIGHT && next == LEFT) {
      return true;
    }
    // After check all if pass return false
    return false;
}

// Give the next position by combining current position and direction
void next_position(int x, int y, direction move, int* next_x, int* next_y) {
  *next_x = x;
  *next_y = y;
  if (move == UP) {
      (*next_y)--;
  } else if (move == DOWN) {
      (*next_y)++;
  } else if (move == LEFT) {
      (*next_x)--;
  } else if (move == RIGHT) {
      (*next_x)++;
  }
}

// Check if the next position hit wall or other player
bool is_hit(int maze[], int x, int y){
// Check if the player hit the wall or any trail
  int index = y * MAZE_WIDTH + x;
    return maze[index] != 0;
}

// Update user position 
void update_player(int* x, int* y, int next_x, int next_y){
  *x = next_x;
  *y = next_y;
}
 
// Mark player's current position as a trail for further drawing
void mark_trail(int maze[], int x, int y, int player){
// Mark player's current position to 1 as a trail
    int index = y * MAZE_WIDTH + x;
    if (player == 1) {
    // If the player1 mark the trail to 2 - blue 
        maze[index] = 2;  
    } else if (player == 2) {
    // If the player2 mark the trail to 3 - yellow
        maze[index] = 3;  
    }
}

// Get the user input and update the direction
void valid_input(int input, direction* player1, direction* player2){
  // User 1 uses arrow key
  if (input == KEY_UP && !reverse_turn(*player1, UP)){
    *player1 = UP;
  } else if (input == KEY_DOWN && !reverse_turn(*player1, DOWN)){
    *player1 = DOWN;
  } else if (input == KEY_RIGHT && !reverse_turn(*player1, RIGHT)){
    *player1 = RIGHT;
  } else if (input == KEY_LEFT && !reverse_turn(*player1, LEFT)){
    *player1 = LEFT;
  // User 2 uses the WASD key
  } else if ((input == 'w') && !reverse_turn(*player2, UP)){
    *player2 = UP;
  } else if ((input == 's') && !reverse_turn(*player2, DOWN)){
    *player2 = DOWN;
  } else if ((input == 'd') && !reverse_turn(*player2, RIGHT)){
    *player2 = RIGHT;
  } else if ((input == 'a') && !reverse_turn(*player2, LEFT)){
    *player2 = LEFT;
  } // Change the player's direction through pointer
}

// Display the game result in a rectangle box
void result_board(bool player1, bool player2) {
  // Initialize the size of the box
  int box_width = 25;
  int box_height = 5;
  int start_y = MAZE_HEIGHT / 2 - box_height / 2;
  int start_x = MAZE_WIDTH - box_width / 2;

  // Draw white box to show result
   // Turn the color on
  attron(COLOR_PAIR(3));
  for (int row = 0; row < box_height; row++) {
    for (int col = 0; col < box_width; col++) {
      mvaddch(start_y + row, start_x + col, ' ');
    }
  }
  // Print black text on white box
  // If player 1 and player 2 hit each other then game tie
  if (player1 && player2) {
    mvprintw(start_y + 1, start_x + 6, "  Tie game!");
  // If player 1 hit the wall then yellow wins
  } else if (player1) {
    mvprintw(start_y + 1, start_x + 4, "  Blue wins!");
  // If player 2 hit the wall then yellow wins
  } else if (player2) {
    mvprintw(start_y + 1, start_x + 5, "  Yellow wins!");
  }
  mvprintw(start_y + 3, start_x + 3, "Press space to exit.");
  attroff(COLOR_PAIR(3));
  refresh();

  nodelay(stdscr, false); // Set up blocking input with getch()
  int input;
  while ((input = getch()) != ' ') {
  }

}

int main() {
  // TODO: Implement the lightcycle game using a game loop
  // Set up ncurses
  initscr();              // Initialize the standard window
  noecho();               // Don't display keys when they are typed
  nodelay(stdscr, true);  // Set up non-blocking input with getch()
  keypad(stdscr, true);   // Allow arrow keys
  curs_set(false);        // Hide the cursor
  // Start the game loop
  bool running = true;
  // Initialize the maze
  int maze[MAZE_WIDTH * MAZE_HEIGHT];
  init_board(maze);
  
  // Initialize the position of each player
  // Player 1 near the upper wall and go down
  int player1_x = MAZE_WIDTH / 2;
  int player1_y = 1;   
  // Player 2 near the lower wall and go up
  int player2_x = MAZE_WIDTH / 2;
  int player2_y = MAZE_HEIGHT - 2; 

  start_color();
  // Color pair 0 is white text on a black background
  init_pair(0, COLOR_WHITE, COLOR_BLACK);
  // Color pair 1 is white text on a blue background
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  // Color pair 2 is white text on a yellow background
  init_pair(2, COLOR_WHITE, COLOR_YELLOW);
  // Color pair 3 is black text on a white background
  init_pair(3, COLOR_BLACK, COLOR_WHITE);

  // Initialize the initial direction of each player
  direction player1 = DOWN;
  direction player2 = UP;

  // Set the inital hit state of each player is false, if player hit something then change to true
  bool player1_hit = false;
  bool player2_hit = false;

  // Mark the original position of each player a trail
  mark_trail(maze, player1_x, player1_y, 1);
  mark_trail(maze, player2_x, player2_y, 2);
  
  // Print the maze
  print_maze(maze);
  refresh();

  while (running){
    // Check the user input
    int input;
    while ((input = getch()) != ERR){
      // Exit when the user types q
      if (input == 'q'){
        running = false;
      } else {
        // Then check the input of the players
        valid_input(input, &player1, &player2);
      }
    }
    print_maze(maze);
    // Initialize the next position of each players
    int next_x1;
    int next_y1;
    int next_x2;
    int next_y2;

    // Calculate next position for players based on current direction
    next_position(player1_x, player1_y, player1, &next_x1, &next_y1);
    next_position(player2_x, player2_y, player2, &next_x2, &next_y2);

    // Check if player will hit the wall or the trail at next position
    player1_hit = is_hit(maze, next_x1, next_y1);
    player2_hit = is_hit(maze, next_x2, next_y2);

    // Check both players move into the same cell at the same time which is then tie game
    if (next_x1 == next_x2 && next_y1 == next_y2) {
    player1_hit = true;
    player2_hit = true;
    }

    // If either player hit somethign then immediately end the game loop
    if (player1_hit || player2_hit) {
      break;
    }

    // Update player positions to their new locations if they don't hit anything
    update_player(&player1_x, &player1_y, next_x1, next_y1);
    update_player(&player2_x, &player2_y, next_x2, next_y2);

    // Mark the new positions as part of each player's trail
    mark_trail(maze, player1_x, player1_y, 1);
    mark_trail(maze, player2_x, player2_y, 2);
    refresh();

    sleep_ms(1000 / FRAME_RATE);

  }
  clear();
  // Draw the final state of the board
  print_maze(maze);
  refresh();
  // Display the game result and wait for user to press space
  result_board(player1_hit, player2_hit);

  // Shut down
  endwin();
}
