// 16.3: Enumerate all nonattacking placements of n-Queens
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>    // std::sort
#include <unordered_set>
#include <unordered_map>

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

int getDiagonal(size_t row, size_t col)
{
  return static_cast<int>(row) - static_cast<int>(col);
}

bool okToPlace(const vector<string> &board, const size_t row, const size_t col,
    const unordered_set<size_t>& freeCols,
    const unordered_map<int, int>& fullDiags,
    const unordered_map<int, int>& fullDiags2)
{
  if (freeCols.find(col) == freeCols.end())
  {
    return false;
  }

  int diag = getDiagonal(row, col);
  auto it = fullDiags.find(diag);
  assert(it != fullDiags.end());
  if (it->second != 0)
  {
    return false;
  }

  int colp = static_cast<int>(board[0].size()) - 1 - col;
  int diag2 = getDiagonal(row, colp);
  auto it2 = fullDiags2.find(diag2);
  assert(it2 != fullDiags2.end());
  if (it2->second != 0)
  {
    return false;
  }

  return true;
}

void placeQueenImpl(vector<string> &board,
    size_t currRow,
    unordered_set<size_t> &freeCols,
    unordered_map<int, int> &fullDiags,
    unordered_map<int, int> &fullDiags2)
{
  cout << __FUNCTION__ << " current row = " << currRow << endl;
  string &row = board[currRow];
  assert(row.size() == board.size());

  size_t i = 0;
  for (i = 0; i < row.size(); i++)
  {
    if (okToPlace(board, currRow, i, freeCols, fullDiags, fullDiags2))
    {
      cout << "Placing Queen at " << "[" << currRow << "][" << i << "]" << endl;

      freeCols.erase(i);
      int diag = getDiagonal(currRow, i);
      ++fullDiags[diag];

      int diag2 = getDiagonal(currRow, board[0].size() - 1 - i);
      ++fullDiags2[diag2];

      board[currRow][i] = OCCUPIED;
      if (currRow == board.size() - 1)
      {
        printBoard(board);
        board[currRow][i] = UNOCCUPIED;
        freeCols.insert(i);
        --fullDiags[diag];
        --fullDiags2[diag2];
        break;
      }
      else
      {
        placeQueenImpl(board, currRow + 1, freeCols, fullDiags, fullDiags2);
      }

      board[currRow][i] = UNOCCUPIED;
      freeCols.insert(i);
      --fullDiags[diag];
      --fullDiags2[diag2];
    }
  }

}

void placeQueen(vector<string> &board)
{
  unordered_set<size_t> freeCols;

  // Key is diagonal number and value is number of queens
  // occupying this diagonal
  // We have two diagonal directions to worry about
  unordered_map<int, int> fullDiags;
  unordered_map<int, int> fullDiags2;

  for (size_t i = 0; i < board[0].size(); i++)
  {
    freeCols.insert(i);
  }

  // For a nxn chessboard, there are n-1 diagonals
  int nDiags = static_cast<int>(board[0].size()*2) - 1;
  int middle = nDiags / 2;
  for (int i = middle*-1; i <= middle; i++)
  {
    fullDiags[i] = 0;
    fullDiags2[i] = 0;
  }

  placeQueenImpl(board, 0, freeCols, fullDiags, fullDiags2);
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

  placeQueen(board);

  return 0;
}
