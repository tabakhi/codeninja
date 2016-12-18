// Find if a subarray in an unsorted array equals to a given 'sum'
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
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

bool findSubArr(const vector<int>& a, const size_t sum)
{
  // a hash map of index to the value
  //unordered_map<size_t, int> imap;

  size_t curr = 0;
  size_t start = 0;
  size_t end = 0;

  for (size_t i = 0; i < a.size(); i++)
  {
    if (a[i] == sum)
    {
      cout << "index " << i << endl;
      return true;
    }

    curr += a[i];

    if (curr == sum)
    {
      cout << "start index " << start <<
        " end index = " << i << endl;;
      printA(a, start, i+1);
      return true;
    }
    else if (curr > sum)
    {
      //for (size_t j = start; j <= i; j++)
      while ((curr > sum) && (start <= i))
      {
        curr -= a[start];
        ++start;

        if (curr == sum)
        {
          cout << "start index " << start << " end index = " << i 
            << endl;;
          printA(a, start, i+1);
          return true;
        }
      }
    }
  }

  return false;
}

int main(int argc, char **argv)
{
    int n;
    vector<int> arr;
    
    for (int i = 1; i < argc-1; i++)
    {
        arr.push_back(atoi(argv[i]));
    }

    printA(arr, 0, arr.size());

    findSubArr(arr, atoi(argv[argc-1]));
    
    return 0;
}
