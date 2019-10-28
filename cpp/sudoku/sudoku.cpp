// Author: Louis Heery (lah119)
// Last Updated: 25/10/19
// File Contents:
// // Functions supplied in skeleton file.
// // Functions created to answer question 1 to 5
// // Other secondary functions used within main functions for question 1 to 5

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "sudoku.h"
using namespace std;

/* You are pre-supplied with the functions below. Add your own
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++)
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}


// =================== Question 1 =================== //
// FUNCTION: Determines if the board is complete
// RETURNS TRUE: if all the cells are filled by digits
// RETURNS FALSE: if above condition is not satisfied
bool is_complete(const char board[9][9]) {
  for (int r = 0; r < 9; r++) {
    for (int i = 0; i < 9; i++) {
      if (!cell_is_filled(board[r][i])) {
        return false;
      }
    }
  }
  return true;
}

// FUNCTION: Determines if a cell is filled
// RETURNS TRUE: if the cell contains a char from '1' to '9' inclusive
// RETURNS FALSE: if above condition not satisfied
bool cell_is_filled(const char cell) {
  if ((cell >= '1') && (cell <= '9')) {
    return true;
  } else {
    return false;
  }
}


// =================== Question 2 =================== //
// FUNCTION: Determines if a particular move is allowed (i.e. obeys rules of sudoku board)
// Rules: (1) coordinates inside range of board, (2) digit between 1 to 9,
//        (3) cell not occupied, (4) digit doesn't exist in row/column/subbox already
// Returns TRUE: if the move is a valid allowed move
// Returns FALSE: if the move is NOT valid allowed move
bool make_move(const char position[2], char digit, char board[9][9]) {

  // Converts coordinate string to integer row and column numbers
  const int row_number = (char) (position[0] - 'A');
  const int column_number = (char) (position[1] - '1');

  // checks the cell reference is valid
  if (row_number < 0 || row_number > 8 || column_number < 0 || column_number > 8)
    return false;

  // checks character is between '1' and '9' inclusive
  if (digit < '1' || digit > '9')
    return false;

  // checks if digit already exists in column
  if (is_column_duplicate(column_number, digit, board))
    return false;

  // checks if digit already exists in row
  if (is_row_duplicate(row_number, digit, board))
    return false;

  // checks if digit already exists in subbox
  if (is_box_duplicate(row_number, column_number, digit, board))
    return false;

  // checks if box is empty
  if (cell_is_filled(board[row_number][column_number]))
    return false;

  // if all conditions are satisified -> board is updated & returns TRUE
  board[row_number][column_number] = digit;
  return true;
}

// FUNCTION: Checks if digit trying to be inserted already exists
// in the same column (TRUE if this is not the case)
bool is_column_duplicate(int column_number, char digit, const char board[9][9]) {

  for (int i = 0; i < 9; i++) { // loops through all cells in the column
    if (board[i][column_number] == digit) {
      return true;
    }
  }
  return false;
}

// FUNCTION: Checks if digit trying to be inserted already exists
// in the same row (TRUE if this is not the case)
bool is_row_duplicate(int row_number, char digit, const char board[9][9]) {
  for (int i = 0; i < 9; i++) { // loops through all cells in the row
    if (board[row_number][i] == digit) {
      return true;
    }
  }
  return false;
}

// FUNCTION: Checks if digit trying to be inserted already exists
// in the same 3x3 box (TRUE if this is not the case)
bool is_box_duplicate(int row_number, int column_number, char digit, const char board[9][9]) {

  // gives row&column coordinates of top-left cell of the current 3x3 subbox
  int row_start = row_number - (row_number % 3);
  int col_start = column_number - (column_number % 3);

  // Returns true if any of the other cells in 3x3 subbox contain same digit
  for (int col_pos = col_start; col_pos < (col_start + 3); col_pos++) {
    for (int row_pos = row_start; row_pos < (row_start + 3); row_pos++) {
      if (board[row_pos][col_pos] == digit) {
        return true;
      }
    }
  }
  // else returns false if no other cell contains the same digit
  return false;
}


// =================== Question 3 =================== //
// FUNCTION: Saves the current board (saved in board[9][9] array) to a .dat file
bool save_board(const char filename[80], const char board[9][9]) {


  try {
    ofstream outputFile;
    outputFile.open(filename);

    // checks character being saved is between '1' and '9' inclusive
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] < '1' || board[i][j] > '9') {
          return false;
        } else {
          // saves character to file if character between 1 and 9
          outputFile << board[i][j];
        }
      }
      outputFile << "\n";
    }

    outputFile.close();

    // returns true if file has been correctly saved
    return true;
  } catch (const exception& e) {return false;}
}


// =================== Question 4 =================== //
// FUNCTION: Recurrsive function which tries to solve the sudoku puzzle read into it via board[9][9] array
bool solve_board(char board[9][9]) {
  int current_row = 0;
  int current_column = 0;

  // Recurrsive function will stop and return true if and when the board is complete
  if(is_complete(board))
    return true;

  // Sets current_row and current_column to the coordinates of the next empty cell
  next_empty(board, current_row, current_column);

  // LOOP through all digits from 1 to 9 inclusive
  for (int digit = 1; digit <= 9; digit++) {

    // Generates Position[2] coordinates array from the array indices (e.g. [5][6] is converted to 'F7')
    char position[2];
    position[0] = (char) (current_row + 65);
    position[1] = (char) (current_column + 49);

    // Converts integer digit value to its equivalent character value
    char actualDigit = digit + '0';

    // Checks if the move is valid
    if (make_move(position, actualDigit, board)) {

      // if move valid -> update value in board[9][9] array
      board[current_row][current_column] = actualDigit;

      // return true if that digit solves the board
      if(solve_board(board)) {
        return true;

      // Else replace empty cell value back with '.' character
      } else {
        board[current_row][current_column] = '.';
      }
    }
  }
  return false;
}

// FUNCTION: Finds the next empty cell after the {current_row, current_column} cell
void next_empty(const char board[9][9], int& current_row, int& current_column) {

  // Cycles through each cell of the board
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      // If cell is empty
      if (!cell_is_filled(board[i][j])) {
        // updates current_row and current_column values
        current_row = i;
        current_column = j;
        return;
      }
    }
  }
}


// =================== Question 5 =================== //
// See 'findings.txt file' for explaination of 'mystery{1,2,3}.dat' boards
// FUNCTION: Polymorphic function that includes number Of Iterations counter
// which keeps track of iterations taken to solve the puzzle.
bool solve_board(char board[9][9], int& numberOfIterations) {

  int current_row = 0;
  int current_column = 0;

  // Recurrsive function will stop and return true if board is complete
  if (is_complete(board))
    return true;

  // Sets current_row and current_column to the coordinates of the next empty cell
  next_empty(board, current_row, current_column);

  // LOOP through all digits from 1 to 9 inclusive
  for (int digit = 1; digit <= 9; digit++) {

    // Generates Position[2] coordinates array from the array indices
    char position[2];
    position[0] = (char) (current_row + 65);
    position[1] = (char) (current_column + 49);

    // Converts integer digit value to its equivalent character value
    char actualDigit = digit + '0';

    // Tests if the move is valid
    if (make_move(position, actualDigit, board)) {

      // if move valid -> update value in board[9][9] array
      board[current_row][current_column] = actualDigit;

      if(solve_board(board, numberOfIterations)) {
        return true;
      } else {
        // Increases iteration counter by 1 if solve_board not true
        numberOfIterations++;

        //replace empty cell value back with '.' character
        board[current_row][current_column] = '.';
      }
    }
  }
  return false;
}
