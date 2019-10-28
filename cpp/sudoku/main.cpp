// Author: Louis Heery (lah119)
// Last Updated: 25/10/19

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << "\n\n";

  cout << "Calling load_board():" << '\n';
  load_board("easy.dat", board);

  cout << '\n' << "Displaying Sudoku board with display_board():" << '\n';
  display_board(board);
  cout << "Done!" << "\n\n";

  cout << "=================== Question 1 ===================" << "\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << "\n\n";


  cout << "=================== Question 2 ===================" << "\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  // Test moves which should not be allowed by sudoku.cpp
  cout << "\n\nTrying move in already occupied cell is ";
  if (!make_move("A7", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  cout << "\n\nTrying move of value already in same row/column is ";
  if (!make_move("A1", '1', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  cout << "\n\nTrying move of value already in same subbox is ";
  if (!make_move("A1", '4', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  cout << "\n\nTrying move of value in invalid cell reference is ";
  if (!make_move("J1", '4', board))
    cout << "NOT ";
  cout << "a valid move. The board is:" << '\n';
  display_board(board);

  cout << "=================== Question 3 ===================" << "\n\n";

  // Load and then save copy of easy, medium and mystery1 board
  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  load_board("medium.dat", board);
  if (save_board("medium-copy.dat", board))
    cout << "Save board to 'medium-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  load_board("mystery1.dat", board);
  if (save_board("mystery1-copy.dat", board))
    cout << "Save board to 'mystery1-copy.dat' successful." << '\n';
  else
    cout << "Save board failed." << '\n';
  cout << '\n';

  cout << "=================== Question 4 ===================" << "\n\n";

  // Tries to solve easy, medium, mystery1, mystery2, mystery3 sudoku boards
  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << '\n';
    save_board("easy-solution.dat", board);
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << '\n';
    save_board("medium-solution.dat", board);
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << '\n';
    save_board("mystery1-solution.dat", board);
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << '\n';
      save_board("mystery2-solution.dat", board);
      display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << '\n';
    save_board("mystery3-solution.dat", board);
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';


  cout << "=================== Question 5 ===================" << "\n\n";

  // Calculates number of iterations required to solve mystery sudoku boards
  load_board("mystery1.dat", board);
  int numberOfIterations = 0;
  if (solve_board(board, numberOfIterations)) {
    cout << "The 'mystery1' board has a solution:" << '\n';
    cout << "Number of Iterations required to solve: " << numberOfIterations << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("mystery2.dat", board);
  numberOfIterations = 0;
  if (solve_board(board, numberOfIterations)) {
    cout << "The 'mystery2' board has a solution:" << '\n';
    cout << "Number of Iterations required to solve: " << numberOfIterations << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  load_board("mystery3.dat", board);
  numberOfIterations = 0;
  if (solve_board(board, numberOfIterations)) {
    cout << "The 'mystery3' board has a solution:" << '\n';
    cout << "Number of Iterations required to solve: " << numberOfIterations << endl;
    display_board(board);
  } else
    cout << "A solution cannot be found." << '\n';
  cout << '\n';

  return 0;
}
