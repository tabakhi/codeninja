#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

int partition(int *a, int left, int right, int pivotindex)
{
    cout << __func__ << " left = " << left << " " << "right = "
    << right << " pivotindex = " << pivotindex << 
    " pivot element = " << a[pivotindex] << endl;

    int pivotval = a[pivotindex];

    // swap pivotval with right most value
    int tmp = a[right];
    a[right] = pivotval;
    a[pivotindex] = tmp;

    int si = left; // store index
    for (int i = left; i <= right-1; i++)
    {
        if (a[i] < pivotval)
        {
            int tmp = a[si];
            a[si++] = a[i];
            a[i] = tmp;
        }
    }

    tmp = a[right];
    a[right] = a[si];
    a[si] = tmp;

    cout << "Pivot element " << tmp << " was placed at index " 
        << si << endl;
    return si;
}

void printA(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << "\t";
    }
    cout << endl;
}

// find the nth element
int quickselect(int *a, int left, int right, int n, int N)
{
    cout << __func__ << " left = " << left << " " << "right = "
    << right << " n = " << n << endl;

    if (left == right)
        return a[left];

    int pivotindex = left + (rand() % (right - left + 1));

    int index = partition(a, left, right, pivotindex);

    cout << "After that array contents are: " << endl;
    printA(a, N);

    if (index == n)
    {
        return a[index];
    }
    else if (index > n)
    {
        // TODO: zero should be changed to left
        return quickselect(a, 0, index-1, n, N);
    }
    else
    {
        return quickselect(a, index+1, right, n, N);
    }

}

int main(int argc, char **argv)
{
    uint32_t k = atoi(argv[1]);

    int a [] = {7, 14, 10, 12, 2, 11, 29, 3, 4};

    int kc = quickselect(a, 0, 8, k-1, sizeof(a)/sizeof(a[0]));

    cout << kc << " is the " << k << "th element" << endl;
    printA(a, sizeof(a)/sizeof(a[0]));

    return 0;
}
