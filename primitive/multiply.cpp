// 5.5 Compute x*y without using multiply or add 
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

int add(int a, int b)
{
  //return a+b;
  int y = b;
  while (y) {
    int carry = a & y;
    a ^= y;

    y = carry << 1;
  }

  return a;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
      cerr << "Usage: " << argv[0] << "n1 n2" << endl;
      return -1;
    }

    int p = atoi(argv[1]);
    int q = atoi(argv[2]);
    int origq = q;
    int origp = p;

    int product = 0;
    while (q) {

      cout << "p = " << p << " q = " << q << endl;
      if (q & 1) {
        product = add(product, p);
      }

      q >>= 1;
      p <<= 1;
    }

    q = origq;
    p = origp;
    cout << p << "*" << q << " = " << product << endl;
}
