// Toggle all the bits of a number except the kth bit
// http://www.geeksforgeeks.org/toggle-bits-number-except-k-th-bit/
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <inttypes.h>

using namespace std;

int main(int argc, char **argv)
{
    uint32_t n = strtoul(argv[1], NULL, 10);
    cout << "Input number is " << n << endl;

    uint32_t k = strtoul(argv[2], NULL, 10);
    cout << "Toggle all bits except the " << k << "th bit" << endl;

    uint32_t mask = 1 << k;
    cout << "Mask is " << mask << endl;

    uint32_t kth = n & mask;
    cout << "kth bit value " << kth << endl;

    uint32_t comp = ~n;
    cout << "complement is " << comp << endl;
    
    uint32_t toggled = 0;
    
    if (kth)
    {
      toggled = comp | kth;
    }
    else
    {
      toggled = comp & (~mask);
    }
    cout << "Toggled value is " << toggled << endl;
    return 0;
}
