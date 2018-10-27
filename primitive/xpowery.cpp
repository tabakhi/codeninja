// Compute x^y where x is a double and y is an integer
// It should be O(n) where n is the number of bits in y
// Assume multiplication, addition, division take constant time
// You cannot use any library functions except those you write youself
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>
#include <errno.h>
#include <iostream>

using namespace std;

#if 0
  else if (k == 2) {
    if (cache.find(k) == cache.end()) {
      result = x *x;
      cache[k] = result;
    }
    else {
      result = cache[k];
    }
  }
  else {
    if (cache.find(k) == cache.end()) {
      double res2 = powerImpl(x, k/2, cache);
      result = res2 * res2;
      cache[k] = result;
    }
    else {
      result = cache[k];
    }
  }
#endif

int num_ops = 0;

double
powerImpl(double x, int k, unordered_map<int, double> &cache)
{
  cout << "power " << k << (cache.find(k) != cache.end() ? " is in cache" : " not in cache") << endl;

  if (cache.find(k) != cache.end()) {
    return cache[k];
  }

  double result = 0;
  if (k == 1) {
    result = x;
  }
  else  {
    double res2 = powerImpl(x, k/2, cache);
    result = res2 * res2;
    ++num_ops;
  }

  cache[k] = result;
  return result;
}

unordered_map<int, double> answerCache;

double
power(double x, int k)
{
  return powerImpl(x, k, answerCache);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
      cerr << "Usage: " << argv[0] << " x y" << endl;
      return -1;
    }

    double x = strtod(argv[1], nullptr);
    int y = atoi(argv[2]);

    vector<int> powers;
    int i = 0;
    while (y)
    {
      int p = y & (1 <<i);
      y &= ~(1<<i);
      i++;
      if (p)
      {
        cout << p << endl;
        powers.push_back(p);
      }
    }

    double answer = 0;
    bool first = true;
    for (size_t j = 0; j < powers.size(); j++)
    {
      if (powers[j] == 0)
        continue;
      cout << "Raising to power " << powers[j] << endl;
      if (first) {
        answer = power(x, powers[j]);
        first = false;
      }
      else {
        answer *= power(x, powers[j]);
        ++num_ops;
      }
      
    } // for

    cout << answer << endl;
    cout << "num operations = " << num_ops << endl;
    return 0;
}
