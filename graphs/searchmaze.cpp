// 19.1: Search a maze
// Find a path from start to end cell
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
findPathImpl(int **maze,
const int n,
const pair<int, int> curr,
const pair<int, int> &start,
const pair<int, int> &end,
std::set<pair<int, int> > &currentPath)
{
  if (curr.first == end.first && curr.second == end.second)
  {
    return true;
  }

  std::vector<pair<int, int> > neighbors = getNeighbors(curr.first, curr.second, n);
  for (size_t k = 0; k < neighbors.size(); k++)
  {
    int ki = neighbors[k].first;
    int kj = neighbors[k].second;

    if (maze[ki][kj] == 1)
      continue;

    if (currentPath.find(neighbors[k]) != currentPath.end())
      continue;

    currentPath.insert(neighbors[k]);

    if (findPathImpl(maze, n, neighbors[k], start, end, currentPath))
      return true;
    else
      currentPath.erase(neighbors[k]);
  }

  return false;
}

void plotPath(int **maze, int n, const std::set<pair<int, int> > &path)
{
  // The order in which we plot the path doesn't matter, it is easy 
  // to visualize the correct path once plotted
  for (std::set<pair<int, int> >::const_iterator it=path.begin(); it!=path.end(); ++it)
  {
    maze[it->first][it->second] = 2;
  }
}

std::set<pair<int, int> >
findPath(int **maze, const int n, pair<int, int> &start, pair<int, int> &end)
{  
  std::set<pair<int, int> > currPath;

  currPath.insert(start);
  findPathImpl(maze, n, start, start, end, currPath);
  plotPath(maze, n, currPath);

  return currPath;
}

void printMaze(int ** maze, int n)
{
  // Print upside down, because that's how we have read it from the file
  for (int i = n-1; i >= 0; i--)
  {
    for (int j = 0; j < n; j++)
    {
      cout << maze[i][j] << " ";
    }
    cout << endl;
  }
}

int main(int argc, char **argv)
{
  std::pair<int, int> start;
  std::pair<int, int> end;
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
      iss >> end.first;
      iss >> end.second;
    }
    else if (nLines == 3)
    {
      iss >> n;

      // allocate n pointers for n rows
      cout << "Allocating maze of " << n << " x " << n << endl;
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
        cout << "Done reading maze" << endl;
        break;
      }
    }
  }

  printMaze(maze, n);
  std::set<pair<int, int> > path = findPath(maze, n, start, end);

  cout << "Printing path from S to E using 2's as markers" << endl;
  printMaze(maze, n);
  return 0;
}
