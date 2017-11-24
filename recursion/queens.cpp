// 16.3: Enumerate all nonattacking placements of n-Queens
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>    // std::sort

using namespace std;

#define OCCUPIED 'Q'
#define UNOCCUPIED '.'

void printBoard(const vector<string> &board)
{
  for (size_t i = 0; i < board.size(); i++)
  {
    cout << board[i] << endl;
  }
}

bool inBoundsR(size_t col, size_t offset, size_t n)
{
  if (col + offset > n)
  {
    return false;
  }

  return true;
}

bool inBoundsL(size_t col, size_t offset, size_t n)
{
  if (col < offset)
  {
    return false;
  }

  return true;
}

bool okToPlace(const vector<string> &board, const size_t row, const size_t col)
{
  for (size_t i = 0; i < row; i++)
  {
    // Check if this column is occupied in any of the above rows
    if (board[i][col] == OCCUPIED)
    {
      return false;
    }

    size_t k = row - i; // distance on diagonal
    // Check left diagonal
    if (inBoundsL(col, k, board[i].size()) &&
        board[i][col - k] == OCCUPIED)
    {
      return false;
    }

    // Check right diagonal
    if (inBoundsR(col, k, board[i].size()) &&
        board[i][col + k] == OCCUPIED)
    {
      return false;
    }
  }

  return true;
}

void placeQueen(vector<string> &board, size_t currRow)
{
  cout << __FUNCTION__ << " current row = " << currRow << endl;
  string &row = board[currRow];
  assert(row.size() == board.size());

  size_t i = 0;
  for (i = 0; i < row.size(); i++)
  {
    if (okToPlace(board, currRow, i))
    {
      cout << "Placing Queen at " << "[" << currRow << "][" << i << "]" << endl;
      board[currRow][i] = OCCUPIED;
      if (currRow == board.size() - 1)
      {
        printBoard(board);
        board[currRow][i] = UNOCCUPIED;
        break;
      }
      else
      {
        placeQueen(board, currRow + 1);
      }

      board[currRow][i] = UNOCCUPIED;
    }
  }

}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " " << "n" << endl;
    return -1;
  }

  size_t n = atoi(argv[1]);
  vector<string> board;
  for (size_t i = 0; i < n; i++)
  {
    string s(n, '.');
    board.push_back(s);
  }

  placeQueen(board, 0);


  return 0;
}
