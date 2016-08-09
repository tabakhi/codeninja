// The fisher yates shuffle
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>

using namespace std;

void printA(const vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main(int argc, char **argv)
{
    // Read the numbers from file
    ifstream inFile(argv[1]);

    int n;
    vector<int> arr;
    while (inFile >> n)
    {
        arr.push_back(n);
    }

    // Generate a random index and put the value there at the
    // end of the list
    // Shrink the working list in each iteration

    // Seed the random number generator
    struct timeval tv;
    assert(gettimeofday(&tv, NULL) == 0);
    srandom(tv.tv_sec);

    printA(arr);
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        int j = random() % (i + 1);
        std::swap(arr[i], arr[j]);

        cout << "Exchanging items at " << j << " with " << i << endl;
        printA(arr);
    }

    return 0;
}
