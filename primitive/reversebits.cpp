// 5.3 write a function that takes a 64 bit word x and returns a 
// 64 bit word consisting of the bits of x in reverse order
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

int main(int argc, char **argv) {

    if (argc != 2)
    {
      cerr << "Usage: " << argv[0] << " number" << endl;
      return -1;
    }

    errno = 0;
    uint64_t n = strtoul(argv[1], NULL, 0);
    assert(errno == 0);
    cout << hex << n << endl;

    uint64_t lmask = 0x8000000000000000;
    uint64_t rmask = 0x1;

    for (uint32_t i = 0; i < 32; i++)
    {
      uint64_t h = (n & lmask);
      uint64_t l = (n & rmask);

      if (h && !l)
      {
        n &= ~h;
        n |= rmask;
      }
      else if (!h && l)
      {
        n &= ~l;
        n |= lmask;
      }

      lmask >>= 1;
      rmask <<= 1;

      cout << "left mask = " << hex << lmask << " ";
      cout << "right mask = " << hex << rmask << " ";
      cout << "number is now = " << hex << n << endl;
    }

    cout << "Bit reversed number is " << hex << n << endl;
    return 0;
}
