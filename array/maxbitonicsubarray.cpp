// http://www.geeksforgeeks.org/maximum-sum-bitonic-subarray/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  //code

  vector<int> arr;

  for (int i = 1; i <= argc - 1; i++)
  {
    arr.push_back(atoi(argv[i]));
  }

  int prev;
  int maxSum = INT_MIN;
  int currSum = 0;
  bool findIncreasing = true;

  for (size_t i = 0; i < arr.size(); i++)
  {
    if (i == 0)
    {
      currSum = arr[i];
      prev = arr[i];
      continue;
    }

    if (arr[i] >= prev && findIncreasing)
    {
      currSum += arr[i];
    }
    else if (arr[i] < prev && findIncreasing)
    {
      currSum += arr[i];
      findIncreasing = false;
    }
    else if (arr[i] <= prev && !findIncreasing)
    {
      currSum += arr[i];
    }
    else if (arr[i] > prev && !findIncreasing)
    {
      if (currSum > maxSum)
      {
        maxSum = currSum;
      }
      currSum = prev + arr[i];
      findIncreasing = true;
    }

    prev = arr[i];
  }

  if (currSum > maxSum)
  {
    maxSum = currSum;
  }

  cout << maxSum << endl;
  return 0;
}
