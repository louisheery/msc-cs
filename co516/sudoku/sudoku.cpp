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
// Function determines if the board is complete
// RETURNS TRUE: if all the cells are filled
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

// Function determines if a cell is filled
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
// Returns TRUE: if the move is a valid allowed move
// Returns FALSE: if the move is NOT valid allowed move
bool make_move(const char position[2], char digit, char board[9][9]) {

  const int row_number = (char) (position[0] - 'A');
  const int column_number = (char) (position[1] - '1');

  if (row_number < 0 || row_number > 8 || column_number < 0 || column_number > 8) // cell reference valid
    return false;

  if (digit < '1' || digit > '9') // character must be between '1' and '9' inclusive
    return false;

  if (is_column_duplicate(column_number, digit, board)) // does character already exist in same column?
    return false;
  if (is_row_duplicate(row_number, digit, board)) // does character already exist in same row?
    return false;
  if (is_box_duplicate(row_number, column_number, digit, board)) // does character already exist in same 3x3 box?
    return false;
  if (cell_is_filled(board[row_number][column_number])) // is cell already filled?
    return false;

  // if all conditions are satisified (i.e. move = valid), then board is updated & returns TRUE
  board[row_number][column_number] = digit;
  return true;
}

// FUNCTION: Checks if digit trying to be inserted already exists in the same column (TRUE if this is not the case)
bool is_column_duplicate(int column_number, char digit, const char board[9][9]) {

  for (int i = 0; i < 9; i++) { // loops through all cells in the column
    if (board[i][column_number] == digit) {
      return true;
    }
  }
  return false;
}

// FUNCTION: Checks if digit trying to be inserted already exists in the same row (TRUE if this is not the case)
bool is_row_duplicate(int row_number, char digit, const char board[9][9]) {
  for (int i = 0; i < 9; i++) { // loops through all cells in the row
    if (board[row_number][i] == digit) {
      return true;
    }
  }
  return false;
}

// FUNCTION: Checks if digit trying to be inserted already exists in the same 3x3 box (TRUE if this is not the case)
bool is_box_duplicate(int row_number, int column_number, char digit, const char board[9][9]) {

  int row_start = row_number - (row_number % 3); // row coordinate of top-left cell of the current 3x3 box
  int col_start = column_number - (column_number % 3); // column coordinate of top-left cell of the current 3x3 box

  for (int col_pos = col_start; col_pos < (col_start + 3); col_pos++) { // loops through all columns in 3x3 box
    for (int row_pos = row_start; row_pos < (row_start + 3); row_pos++) { // loops through all rows in 3x3 box
      if (board[row_pos][col_pos] == digit) {
        return true;
      }
    }
  }
  return false;
}


// =================== Question 3 =================== //
// FUNCTION: Saves the current board (saved in board[9][9] array) to a .dat file
bool save_board(const char filename[80], const char board[9][9]) {

  // TODO: NEED TO ADD MORE CHECKS i.e. making sure that each character that is added is correct.
  try {
    ofstream outputFile;
    outputFile.open(filename);
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] < '1' || board[i][j] > '9') { // checks character being saved is between '1' and '9' inclusive
          return false;
        } else {
          outputFile << board[i][j];
        }
      }
      outputFile << "\n";
    }

    outputFile.close();

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

    char actualDigit = digit + '0'; // Converts integer digit value to its equivalent character value

    if (make_move(position, actualDigit, board)) { // Tests if the move is valid
      board[current_row][current_column] = digit + '0'; // if move valid -> update value in board[9][9] array

      if(solve_board(board)) {
        return true;
      } else { // ELSE: replace empty cell value back with '.' character
        board[current_row][current_column] = '.';
      }
    }
  }
  return false;
}

// FUNCTION: Finds the next empty cell after the {current_row, current_column} cell
void next_empty(const char board[9][9], int& current_row, int& current_column) {
  for (int i = 0; i < 9; i++) { // Cycles through each row of board
    for (int j = 0; j < 9; j++) { // Cycles through each column of board
      if (!cell_is_filled(board[i][j])) {
        current_row = i; // updates current_row and current_column values
        current_column = j;
        return;
      }
    }
  }
}


// =================== Question 5 =================== //
// See 'findings.txt file' for explaination of 'mystery{1,2,3}.dat' boards
