# Rock Paper Scissor

This lab is a single-player Rock Paper Scissor game written in C for CSC 161.

## Overview

The player plays against the computer. On each round:

- the computer randomly chooses rock, paper, or scissors
- the player chooses rock, paper, or scissors by entering a number
- the program prints both choices
- the program says whether the player won, lost, or tied
- the program updates the running score

After each round, the player can choose whether to play again.

## How To Play

When prompted, enter one of these numbers:

- `1` = Rock
- `2` = Paper
- `3` = Scissors

Example:

```text
What move do you want to play?
1. Rock
2. Paper
3. Scissors
Enter the number of your choice: 2
```

After the round ends, enter:

- `1` to play again
- `2` to stop playing

## Scoring

The program keeps track of:

- wins
- ties
- losses

The score is printed after each round.

## Compile And Run

If you are compiling directly with `clang`, use:

```bash
clang rps.c -o rps
./rps
```

If your course starter files include a `Makefile`, you can also use:

```bash
make
./rps
```

## Files

- `rps.c` - source code for the lab
- `README.md` - lab description and instructions

## Notes

- The computer's choice is generated with `rand()`.
- The random number generator is seeded with `time(NULL)`.
- Input validation asks the player to enter another choice if the number is not valid.
