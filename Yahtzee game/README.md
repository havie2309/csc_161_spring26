# Yahtzee Game

This project is a simplified single-player version of Yahtzee written in C for CSC 161.

## Overview

In this game, the player completes 6 turns. On each turn:

- 5 dice are rolled.
- The player chooses which dice to keep and which dice to re-roll.
- The player gets one more re-roll choice.
- The player stores the final result in one unused score line.

The score lines match the six basic Yahtzee categories:

- `1` = Ones
- `2` = Twos
- `3` = Threes
- `4` = Fours
- `5` = Fives
- `6` = Sixes

Each score line can only be used once. At the end of the game, the program prints the score in every line and the total score.

## How To Play

When the program asks which dice to keep, enter **five numbers** separated by spaces:

- `1` means keep that die
- `0` means re-roll that die

Example:

```text
1 1 0 0 1
```

After the final roll, choose where to store the score by entering a number from `1` to `6`.

The score for that line is calculated by adding only the dice that match the chosen line number.

Examples:

- Choosing line `1` adds all dice showing `1`
- Choosing line `4` adds all dice showing `4`
- Choosing line `6` adds all dice showing `6`

## Compile And Run

If you are compiling directly with `clang`, use:

```bash
clang yahtzee.c -o yahtzee
./yahtzee
```

If your course starter files include a `Makefile`, you can also use:

```bash
make
./yahtzee
```

## Files

- `yahtzee.c` - source code for the game
- `README.md` - project description and instructions

## Notes

- The game uses random dice rolls with `rand()` and `time(NULL)`.
- Input validation is included for reroll choices and score line selection.
