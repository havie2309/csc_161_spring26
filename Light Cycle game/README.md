# Light Cycle Game

This project is a two-player Light Cycle game written in C for CSC 161.

## Overview

Light Cycle is inspired by the arcade-style game from *Tron*. Two players move around a rectangular grid while leaving trails behind them. The goal is to survive longer than the other player.

The game board has:

- 35 playable columns
- 25 playable rows
- a solid border around the playable area

Each lightcycle moves forward automatically. A player crashes if their lightcycle moves into:

- the border
- their own trail
- the other player's trail

If one player crashes first, the other player wins. If both players crash at the same time, the game ends in a tie.

## Controls

Player 1 is blue and uses the arrow keys:

- Up arrow = move up
- Down arrow = move down
- Left arrow = move left
- Right arrow = move right

Player 2 is yellow and uses `W`, `A`, `S`, and `D`:

- `W` = move up
- `S` = move down
- `A` = move left
- `D` = move right

The game does not allow a player to make a 180-degree turn in one move. For example, a player moving left cannot immediately turn right.

## Display

The game uses `ncurses` to draw the board in the terminal.

- Empty cells are shown with a black background.
- Player 1's trail is shown with a blue background.
- Player 2's trail is shown with a yellow background.
- Each grid cell is printed as two adjacent terminal characters so the board appears closer to square.

When the game ends, a message shows whether blue won, yellow won, or the game ended in a tie. Press the space bar to exit after the result appears.

## Implementation Notes

The board is represented with a one-dimensional array.

- `0` represents an empty cell
- `1` represents the border
- `2` represents player 1's blue trail
- `3` represents player 2's yellow trail

The program uses a game loop that:

- reads keyboard input without stopping the game
- updates each player's direction
- calculates the next position for each player
- checks whether either player has crashed
- marks each player's new position as part of their trail

## Compile And Run

Because this program uses `ncurses`, link the ncurses library when compiling directly with `clang`:

```bash
clang lightcycle.c -o lightcycle -lncurses
./lightcycle
```

If your course starter files include a `Makefile`, you can also use:

```bash
make
./lightcycle
```

## Files

- `lightcycle.c` - source code for the game
- `README.md` - project description and instructions

## Notes

- The game runs at 4 frames per second.
- The initial blue lightcycle starts near the top of the board and moves down.
- The initial yellow lightcycle starts near the bottom of the board and moves up.
