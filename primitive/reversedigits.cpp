// 5.10: Reverse Digits
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>
#include <errno.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
      cerr << "Usage: " << argv[0] << " number" << endl;
      return -1;
    }

    int n = atoi(argv[1]);
    int mult = 1;

    if (n < 0)
    {
      n *= -1;
      mult = -1;
    }
    int nr = 0;

    while (n)
    {
      int r = n % 10;
      n = n / 10;

      if (nr)
      {
        nr *= 10;
      }
      nr += r;
    }

    cout << "reversed number is " << nr*mult << endl;
    return 0;
}
