// http://www.codewars.com/kata/is-my-friend-cheating/cpp
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
  int n = atoi(argv[1]);

  int totalSum = (n * (n + 1)) / 2;

  int a = 1;
  int b = n;

  int prevA = 0, prevB = 0;

  while (a < b)
  {
    int sum = totalSum - (a + b);
    int product = a * b;

    cout << "a = " << a << " b = " << b << " sum = " << sum <<
    " product = " << product << endl;

    if (sum == product)
    {
      cout << a << " " << b << endl;
      if (prevA == a-1)
      {
        prevA = a++;
      }
      else
      {
        prevA = a--;
      }
    }
    else if (sum > product)
    {
      prevA = a++;
    }
    else
    {
      prevB = b--;
    }
  }

  return 0;
}

