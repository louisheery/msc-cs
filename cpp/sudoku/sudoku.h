// Author: Louis Heery (lah119)
// Last Updated: 25/10/19

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(const char board[9][9]);
bool cell_is_filled(const char cell);
bool make_move(const char position[2], char digit, char board[9][9]);
bool is_column_duplicate(int column_number, char digit, const char board[9][9]);
bool is_row_duplicate(int row_number, char digit, const char board[9][9]);
bool is_box_duplicate(int row_number, int column_number, char digit, const char board[9][9]);
bool save_board(const char filename[80], const char board[9][9]);
bool solve_board(char board[9][9]);
void next_empty(const char board[9][9], int& current_row, int& current_column);
bool solve_board(char board[9][9], int& numberOfIterations);
