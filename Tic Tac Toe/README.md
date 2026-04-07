# Tic Tac Toe Game

This lab is a two-player Tic Tac Toe game written in C for CSC 161.

## Overview

The game is played on a 3 by 3 board. Two players take turns placing their marks:

- Player 1 uses `X`
- Player 2 uses `O`

The game ends when:

- one player gets three marks in a row
- the board fills completely with no winner

Three in a row can be horizontal, vertical, or diagonal.

## How To Play

On each turn, the program prints the current board and then prints a version of the board showing the available move numbers.

Choose a space by entering a number from `1` to `9`.

Example:

```text
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9
Enter the number of the cell to place an X: 5
```

After a move is entered, the program places the current player's mark in that cell and switches to the other player.

If a selected space is already occupied, the program asks the player to choose again.

## Winning And Ties

The program checks for a winner after each move.

A player wins by placing three marks in a row:

- across a row
- down a column
- across either diagonal

If all nine spaces are filled and no player has won, the game ends in a tie.

After each game, the program asks whether the players want to play again.

## Implementation Notes

The board is represented with a one-dimensional array of 9 characters.

- Empty spaces are stored as `' '`
- Player X's spaces are stored as `'X'`
- Player O's spaces are stored as `'O'`

The board uses row-major order:

- indexes `0`, `1`, and `2` are the top row
- indexes `3`, `4`, and `5` are the middle row
- indexes `6`, `7`, and `8` are the bottom row

The program uses helper functions to:

- print the board
- show the available moves
- read a player's move
- check for a win
- check for a tie
- ask whether to play again

## Compile And Run

If you are compiling directly with `clang`, use:

```bash
clang game.c -o game
./game
```

If your course starter files include a `Makefile`, you can also use:

```bash
make
./game
```

## Files

- `game.c` - source code for the game
- `README.md` - project description and instructions

## Notes

- The game alternates turns between `X` and `O`.
- The replay prompt accepts `Y` to play again or `N` to stop.
- The program uses `fgets` for reading player input.
