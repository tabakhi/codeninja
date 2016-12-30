// 5.11 Check if a decimal integer is a palindrome
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

size_t numdigits(int n)
{
  int divisor = 1;
  int i = 0;
  for (i = 1; i < 10; i++)
  {
    divisor *= 10;

    if (n < divisor)
    {
      break;
    }
  }

  return i;
}

bool isDecimalPalindrome(int n)
{
  // The string representation of an int can be maximum 10 chars long
  // If negative the number is written usually with '-' prefix
  // E.g. -333
  if (n < 0)
  {
    return false;
  }
  else if (n == 0 || n < 10)
  {
    return true;
  }

  size_t digits = numdigits(n);
  cout << "num digits = " << digits << endl;

  int nh = n;
  int nl = n;

  int divisor = int(pow(10, digits-1));
  cout << "Initial divisor = " << divisor << endl;

  for (size_t i = 0; i < digits/2; i++)
  {
    int qh = nh/divisor;
    nh -= qh * divisor;
    divisor /= 10;

    int ml = nl % 10;
    nl /= 10;

    cout << "ml = " << ml << " " << "qh = " << qh << endl;
    if (ml != qh)
    {
      return false;
    }
  }

  return true;
}

int main(int argc, char **argv) {

    if (argc != 2)
    {
      cerr << "Usage: " << argv[0] << " number" << endl;
      return -1;
    }

    int n = atoi(argv[1]);
    cout << (isDecimalPalindrome(n) ? "palindrome" : "not a palindrome") << endl;
    return 0;
}
