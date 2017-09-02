// Find the smallest missing positive number from an array
// http://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array/
// Constraints:
// Array can have positive and negative numbers and can have
// duplicates.
// You can use only constant extra space and code should run in
// O(n) time
// You can modify the original array
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

void printA(const vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int
findSmallestMissing(vector<int> &arr)
{
  size_t si = 0;
  for (size_t i = 0; i < arr.size(); i++)
  {
    if (arr[i] <= 0)
    {
      swap(arr[i], arr[si++]);
    }
  }

  int min = INT_MAX;
  int max = INT_MIN;

  for (size_t i = si; i < arr.size(); i++)
  {
    if (arr[i] < min)
    {
      min = arr[i];
    }

    if (arr[i] > max)
    {
      max = arr[i];
    }
  }

  cout << "min = " << min << " " << "max = " << max << endl;

  size_t i = si;
  int tmp = 0;
  while (i < arr.size())
  {
    cout << "i = " << i << endl;
    printA(arr);

    if (arr[i] == 0)
    {
      cout << i << " location has zero" << endl;
      i++;
    }
    else if (arr[i] > arr.size() - si)
    {
      cout << arr[i] << " at location " << i << " is outside range"
        << endl;
      cout << "Setting location to zero" << endl;

      arr[i] = 0;
    }
    else if (arr[i] != i - si + 1)
    {
      if (arr[arr[i] + si -1] == arr[i]) // duplicate
      {
        cout << arr[i] << " already exists at " << arr[i]-1 << endl;
        arr[i] = 0;
        continue;
      }
      tmp = arr[arr[i] + si - 1];
      arr[arr[i] + si - 1] = arr[i];

      arr[i] = tmp;
    }
    else if (arr[i] == i - si + 1)
    {
      cout << arr[i] << " is in the right place at " << i << endl;
      i++;
    }
  }

  i = si;
  for (i = si; i < arr.size(); i++)
  {
    if (arr[i] != i - si + 1)
    {
      cout << "Smallest missing positive number is " << i - si + 1 << endl;
      return static_cast<int>(i - si + 1);
    }
  }

  cout << "Smallest missing positive number is " << i - si + 1 << endl;
  return i - si + 1;
}

int main(int argc, char **argv)
{
    // Read the numbers from file
    ifstream inFile(argv[1]);

    int n;
    vector<int> arr;
    while (inFile >> n)
    {
        arr.push_back(n);
    }

    // make a copy for verification 
    vector<int> arrCopy = arr;

    printA(arr);
    findSmallestMissing(arr);
    printA(arr);

    return 0;
}
