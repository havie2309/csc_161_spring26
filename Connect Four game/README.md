# Connect Four Game

This project is a two-player Connect Four game written in C for CSC 161.

## Overview

The game is played on a board with:

- 7 columns
- 6 rows

Two players take turns dropping tokens into a column:

- Player 1 uses `Y` for yellow
- Player 2 uses `R` for red

The token falls to the lowest open space in the selected column. The game ends when:

- a player gets 4 tokens in a row horizontally, vertically, or diagonally
- the board fills completely with no winner

## How To Play

When it is your turn, type a column letter from `A` to `G`.

Example:

```text
A
```

The program checks for:

- invalid letters
- extra characters in the input
- full columns

If the move is invalid, the player is asked to enter another column.

## Board Display

The board is printed in the terminal with column labels `A` through `G`.

- `Y` tokens are shown in yellow
- `R` tokens are shown in red

Empty spaces are displayed as blanks until a token is dropped there.

## Implementation Notes

This program represents the board with a **one-dimensional array** of 42 cells instead of a 2D array.

- Board width: `7`
- Board height: `6`
- Total cells: `42`

The board uses row-major order, which means:

- the first 7 elements are the first row
- the next 7 elements are the second row
- and so on

## Compile And Run

If your starter files include a `Makefile`, use:

```bash
make
./game
```

If you want to compile directly with `clang`, use:

```bash
clang game.c -o game
./game
```

## Files

- `game.c` - source code for the Connect Four game
- `README.md` - project description and instructions

## Notes

- The program alternates turns between player `Y` and player `R`.
- A win is detected for horizontal, vertical, and both diagonal directions.
- If all columns are full and no player has won, the game ends in a tie.
