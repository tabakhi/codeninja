// Problem 6.15: Rotate an array
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printA(const vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

void shiftK(vector<int> &arr, int k)
{
    size_t swapped = 0;
    size_t start = k;
    size_t lastIndex = 0;

    int tmp;
    while (swapped != arr.size())
    {
        int dstIndex = 0;

        if (swapped == 0)
        {
            tmp = arr[0]; // must be zero
            arr[0] = arr[k];
            lastIndex = 0;
        }
        else
        {
            int srcIndex = lastIndex; 
            dstIndex = srcIndex - (k); 
            if (dstIndex < 0)
            {
                dstIndex = arr.size() + dstIndex;
            }

            cout << "LastIndex = " << lastIndex << " dstIndex = " << dstIndex << endl;

            assert(dstIndex >= 0);
            assert(dstIndex <= static_cast<int>(arr.size() - 1));

            int tmp2 = arr[dstIndex];
            arr[dstIndex] = tmp;
            tmp = tmp2;

            lastIndex = dstIndex;
        }

        if (dstIndex == start)
        {
            cout << "dstIndex == start " << "(" << start << ")" << endl;
            ++start;
            lastIndex = start;
            tmp = arr[start];
        }

        ++swapped;
        printA(arr);
    }

}

int main(int argc, char **argv)
{
    // Read the numbers from file
    ifstream inFile(argv[1]);

    // Shift by k elements to the left
    int k = atoi(argv[2]);

    int n;
    vector<int> arr;
    while (inFile >> n)
    {
        arr.push_back(n);
    }

    // make a copy for verification 
    vector<int> arrCopy = arr;

    printA(arr);

    shiftK(arr, k);

    for (size_t i = 0; i < arr.size(); i++)
    {
        assert(arr[i] == arrCopy[(i+k) % arr.size()]);
    }

    return 0;
}
