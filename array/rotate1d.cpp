// 6.15 Rotate a 1-d array by k positions to the right
// Same as shift.cpp but doing a second time
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
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

void rotate(vector<int> &a, size_t k)
{
   size_t moved = 0;
   size_t i = 0; // start at the first index
   size_t start = UINT_MAX;
   bool startAssigned = false;
   int curr = a[i];

   while (moved < a.size())
   {
     if (i == start && startAssigned)
     {
       start = ++i;
       curr = a[i];
     }

     if (!startAssigned)
     {
       startAssigned = true;
       start = i;
     }

     // new position
     int j = (i + k) % a.size();

     int tmp = a[j];
     a[j] = curr;
     curr = tmp;
     i = j;

     ++moved;
   }
}

int main(int argc, char **argv)
{
    int n;
    vector<int> arr;
    
    if (argc < 3)
    {
      cerr << "At least 3 arguments must be given" << endl;
    }

    for (int i = 1; i < argc-1; i++)
    {
        arr.push_back(atoi(argv[i]));
    }

    printA(arr, 0, arr.size());

    int k = atoi(argv[argc-1]);

    rotate(arr, k);
    
    printA(arr, 0, arr.size());
    return 0;
}
