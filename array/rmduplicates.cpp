// 6.6 Delete duplicates from a sorted array
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>

using namespace std;

void printArr(int *pArr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << pArr[i] << " ";
    }
    cout << endl;
}

size_t removeDuplicates(int *arr, size_t n)
{
    size_t move = 0;

    for (size_t i = 1; i < n; i++)
    {
        if (arr[i] != arr[i-1])
        {
            if (move)
            {
                arr[i-move] = arr[i];
            }
        }
        else
        {
            ++move;
        }
    }

    // Clear the duplicates at the end to make the output clear
    for (size_t i = n-move; i < n; i++)
    {
        arr[i] = 0;
    }

    return n-move;
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
    size_t k = removeDuplicates(arr, argc - 1);

    cout << "array without duplicates: (new size = " << 
        k << ")" << endl;
    printArr(arr, argc - 1);

    delete [] arr;

    return 0;
}
