# Knight's Tour Solver

This project solves a variation of the classic Knight's Tour Problem. The task is to find a valid sequence of moves for a knight on a chessboard, starting from a given square and ending on a specific target square, while visiting each square on the board at most once.

## Problem Description
The knight is a piece in the game of chess that moves in an "L" shape (two squares in one direction and then one square perpendicular). The objective of this program is to find a valid tour for the knight on a square chessboard of variable size (between 1x1 and 26x26), starting at one square and ending at another, without revisiting any square more than once.

## Key Features
- Accepts command line parameters to specify the board size, starting square, and ending square.
- Validates command line inputs (e.g., checks if the square coordinates are valid based on the board size).
- Implements a backtracking algorithm to find the knight's tour.
- Uses recursive functions to explore all possible knight's moves and determine a valid path.
- Outputs the knight's tour as a sequence of square names (or an error if no valid tour can be found).

## Usage
The program takes three command line parameters:

1. Board size: An integer between 1 and 26.
2. Start square: A valid chess square name (e.g., a1).
3. End square: Another valid chess square name.
