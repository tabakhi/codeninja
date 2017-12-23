// 19.2: Paint a boolean matrix
#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

std::vector<pair<int, int> >
getNeighbors(int i, int j, int n)
{
  std::vector<pair<int, int> > cells;
  
#ifdef MOVEDIAGONAL
  if (i-1 >= 0 && j-1 >= 0)
  {
    cells.push_back(make_pair(i-1, j-1));
  }
#endif

  if (i-1 >= 0)
  {
    cells.push_back(make_pair(i-1, j));
  }

#ifdef MOVEDIAGONAL
  if (i-1 >= 0 && j+1 < n)
  {
    cells.push_back(make_pair(i-1, j+1));
  }
#endif

  if (j-1 >= 0)
  {
    cells.push_back(make_pair(i, j-1));
  }

  if (j+1 < n)
  {
    cells.push_back(make_pair(i, j+1));
  }

#ifdef MOVEDIAGONAL
  if (i+1 < n && j-1 >= 0)
  {
    cells.push_back(make_pair(i+1, j-1));
  }
#endif

  if (i+1 < n)
  {
    cells.push_back(make_pair(i+1, j));
  }

#ifdef MOVEDIAGONAL
  if (i+1 < n && j+1 < n)
  {
    cells.push_back(make_pair(i+1, j+1));
  }
#endif

  return cells;
}

bool
paintMatrixImpl(int **maze,
    const int n,
    const pair<int, int> &current,
    const bool bColor)
{
  maze[current.first][current.second] = !bColor;

  std::vector<pair<int, int> > neighbors =
    getNeighbors(current.first, current.second, n);

  // for each neighbor, if it is bColor, invert it,
  // if it is !bColor, skip traversing it's neighbors
  for (std::vector<pair<int, int> >::const_iterator it = neighbors.begin();
      it != neighbors.end(); it++)
  {
    const pair<int, int> neighbor = make_pair(it->first, it->second);
    if (maze[neighbor.first][neighbor.second] == bColor)
    {
      paintMatrixImpl(maze, n, neighbor, bColor);
    }
  }
}

void
paintMatrix(int **maze, const int n, const pair<int, int> &start)
{
  // 0 -> white, 1 -> black
  // Note original color
  const bool bColor = maze[start.first][start.second];

  paintMatrixImpl(maze, n, start, bColor);
}

void printMatrix(int ** maze, int n, pair<int, int> *start)
{
  // Print upside down, because that's how we have read it from the file
  for (int i = n-1; i >= 0; i--)
  {
    for (int j = 0; j < n; j++)
    {
      if (start && i == start->first && j == start->second)
      {
        cout << 0x18 << " ";
      }
      else
      {
        cout << maze[i][j] << " ";
      }
    }
    cout << endl;
  }
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
      iss >> start.first;
      iss >> start.second;
    }
    else if (nLines == 2)
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

  printMatrix(maze, n, &start);
  paintMatrix(maze, n, start);
  cout << "Painted matrix: " << endl;
  printMatrix(maze, n, NULL);
  return 0;
}
