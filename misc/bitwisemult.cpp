// Multiplication without using multiplication operator
// TODO: Handle negative integers (can convert them to 2's complement)
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int binadd(int x, int y)
{
  while (y != 0)
  {
    int carry = x & y;
    x = x ^ y;

    y = carry << 1;
  }

  return x;
}

int get2power(int x)
{
  if (x == 0)
  {
    cout << "Input arg should be > 0" << endl;
    assert(0);
  }

  int k = 0;
  while (1)
  {
    int n = 1 << k;
    if (n == x)
    {
      break;
    }
    else if (n > x)
    {
      // k--; using 2's complement addition
      k = binadd(k, 0xffffffff);
      break;
    }

    // k++
    k = binadd(k, 1);
  }

  return k;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << "num1 num2" << endl;
        return 2;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int bcopy = b;

    int product = 0;
    int sign = 1;
    if (!a || !b)
    {
      cout << product << endl;
    }
    else if (a < 0 && b > 0)
    {
      sign = -1;
    }
    else if (a > 0 && b < 0)
    {
      sign = -1;
    }
    else
    {
      sign = 1;
    }

    vector<int> pvec;
    // Break b into it's factors of 2 and OR them
    while (b)
    { 
      cout << "b = " << b << endl;
      // The next power of 2 that is less than b
      int p = get2power(b);
      pvec.push_back(p);
      cout << "next power is " << p << endl;

      //b -= (1 << p);
      b = binadd(b, binadd(~(1 << p), 1));
    }

    for (size_t i = 0; i < pvec.size(); i++)
    {
      //product += (a << pvec[i]);
      product = binadd(product, a << pvec[i]);
    }

    assert(product*sign == a*bcopy);
    cout << "product is " << product*sign << endl;
    return 0;
}

