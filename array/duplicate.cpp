// Find a duplicate in a given array of size n which contains all numbers from 1 to n-1 with one duplicate
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/time.h>

using namespace std;

void printA(const vector<int>& a, size_t start, size_t end)
{
  for (size_t k = start; k < end; k++)
  {
    cout << a[k] << " ";
  }
  cout << endl;
}

int findDuplicate(vector<int> &a)
{
  for (size_t i = 0; i < a.size(); i++)
  {
    while (a[i] != i + 1)
    {
      if (a[a[i]-1] == a[i])
        return a[i];
      std::swap(a[a[i]-1], a[i]);
    }
  }
}
int main(int argc, char **argv)
{
    int n;
    vector<int> arr;
    
    for (int i = 1; i < argc; i++)
    {
        arr.push_back(atoi(argv[i]));
    }

    printA(arr, 0, arr.size());
    cout << "The duplicate is " << findDuplicate(arr) << endl;
    
    return 0;
}
