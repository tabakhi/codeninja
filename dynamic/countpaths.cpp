#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

//typedef unordered_map<pair<int, int>, int> PATHMAP;
typedef vector< vector<int> > PATHMAP;

PATHMAP knownpaths;
int **a;

int travel(int cr, int cc, int rows, int cols)
{
  cout << __FUNCTION__ << "[" << cr << "]" << "[" << cc << "]" << endl;

  if (cr == 0 && cc == cols-1)
  {
    knownpaths[cr][cc] = 1;
    return 1;
  }

  //pair<int, int> coord = make_pair<int, int>(cr, cc);
  //if (knownpaths.find(coord) != knownpaths.end())
  if (knownpaths[cr][cc] != -1)
  {
    // We can even delete it from the hash map now as we probably
    // will need it only once after adding it
    return knownpaths[cr][cc];
  }

  // We hit an obstacle
  if (a[cr][cc] == 1)
  {
    knownpaths[cr][cc] = 0;
    return 0;
  }

  int p1 = 0, p2 = 0;

  // There are 2 possible ways forward (go down row, go forward column)
  if (cr-1 >= 0)
  {
    p1 = travel(cr-1, cc, rows, cols);
  }

  if (cc+1 < cols)
  {
    p2 = travel(cr, cc+1, rows, cols);
  }

  knownpaths[cr][cc] = p1 + p2;
  return knownpaths[cr][cc];
}

int main(int argc, char **argv)
{
  std::pair<int, int> start;
  int n;
  int r = 0;
  int **maze;

  string file = argv[1];
  ifstream inFile(file.c_str());
  size_t nLines = 0;
  while (inFile.good())
  {
    string str;
    getline(inFile, str);

    cout << "Line: " << str << endl;

    istringstream iss(str);
    ++nLines;
    if (nLines == 1)
    {
      iss >> n;

      // allocate n pointers for n rows
      cout << "Allocating matrix of " << n << " x " << n << endl;
      maze = new int*[n];
      for (int k = 0; k < n; k++)
      {
        //*(maze + k) = new int[n];
        maze[k] = new int[n];
      }
    }
    else
    {
      // We read it upside down, i.e. the topmost row appears first
      // in the file
      int val;
      for (int k = 0; k < n; k++)
      {
        iss >> val;
        maze[n - 1 - r][k] = val;
      }

      if (++r >= n)
      {
        cout << "Done reading matrix" << endl;
        break;
      }
    }
  } // while

  a = maze;

  for (size_t i = 0; i < n; i++)
  {
    vector<int> row;
    for (size_t j = 0; j < n; j++)
    {
      row.push_back(-1);
    }
    knownpaths.push_back(row);
  }

  cout << "Number of ways " << travel(n-1, 0, n, n) << endl;
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < n; j++)
    {
      cout << knownpaths[i][j] << "  ";
    }
    cout << endl;
  }
  return 0;
}
