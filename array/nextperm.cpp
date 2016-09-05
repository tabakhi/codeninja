// 6.6 Delete duplicates from a sorted array
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sys/time.h>
#include <limits.h>

using namespace std;

void printArr(int *pArr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << pArr[i] << " ";
    }
    cout << endl;
}

bool nextPerm(int *a, size_t n)
{
    // Find from the end where the number is less than the 
    // next one in the sequence
    int i;
    for (i = static_cast<int>(n-2); i >= 0; i--)
    {
        if (a[i] < a[i+1])
        {
            break;
        }
    }

    cout << "i = " << i << endl;

    // Find the least greatest number than a[i]
    int lt = INT_MAX;
    int k = -1;
    for (int j = i+1; j < n && i > 0; j++)
    {
        if (a[j] > a[i] && a[j] < lt)
        {
            lt = a[j];
            k = j;
        }
    }

    cout << "k = " << k << endl;

    // place a[k] at a[i]
    if (k >= 0 && i >= 0)
    {
        std::swap(a[k], a[i]);
    }
    
    // sort all elements between i+1 and n-1
    if (k >= 0)
    {
        std::sort(a+i+1, a+n);
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        return 0;
    }

    int *arr = new int[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        arr[i-1] = atoi(argv[i]);
    }

    cout << "original array:" << endl;
    printArr(arr, argc - 1);

    if ( nextPerm(arr, argc - 1) )
    {
        cout << "next permutation: " << endl;
        printArr(arr, argc - 1);
    }
    else
    {
        cout << "no more permutations" << endl;
    }

    delete [] arr;

    return 0;
}
