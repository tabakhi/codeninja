#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Pair
{
 public:
  Pair() : num(0), index(0) {}
  Pair(int n, size_t i) : num(n), index(i) {}
  bool operator() (Pair &lhs, Pair &rhs)
  {
    return (lhs.num < rhs.num);
  }
  int num;
  size_t index;

};

class PairComparator
{
 public:
  bool operator() (Pair &lhs, Pair &rhs)
  {
    return (lhs.num < rhs.num);
  }
};

void printArray(const vector<Pair> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i].num << " ";
    }

    cout << endl;
}

int main(int argc, char **argv)
{
    // Read the numbers from file
    ifstream inFile(argv[1]);

    int n;
    size_t index = 0;
    vector<Pair> numbers;
    while (inFile >> n)
    {
        numbers.push_back(Pair(n, index++));
    }

    printArray(numbers);
    std::sort(numbers.begin(), numbers.end(), Pair());
    printArray(numbers);

    int start = -1;
    int end = -1;
    for (size_t i = 0; i < numbers.size(); i++)
    {
      if (numbers[i].index != i)
      {
        if (start == -1)
        {
          start = i;
          end = i;
        }
        else
        {
          end = i;
        }
      }

    } // for loop

    cout << "Min unsorted sub array is between " << start << " " << end 
      << endl;

    return 0;
}

