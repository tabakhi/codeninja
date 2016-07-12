#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printArray(const vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}


// partition the vector around the kth element
// I.e. all elements less than a[k] will be on left side
// and all elements greater or equal than a[k] on it's right
// The final position where a[k] will be placed is the 
// return value
int partition(vector<int> &a, size_t lo, size_t hi, size_t k)
{
    // Put a[k] at the right end
    swap(a[k], a[hi]);

    size_t si = lo;

    for (size_t i = lo; i < hi; i++)
    {
        if (a[i] < a[hi])
        {
            swap(a[i], a[si++]);
        }
    }

    swap(a[si], a[hi]);
    return si;
}

void qs(vector<int> &a, size_t lo, size_t hi)
{
    cout << "qs: lo = " << lo << " hi = " << hi << endl;

    if (lo == hi || a.size() == 0)
    {
        return;
    }

    int k = (rand() % (hi - lo + 1)) + lo;
    cout << "Partitioning over k = " << k << endl;

    int m = partition(a, lo, hi, k);

    cout << "Put " << k << " th element at " << m << endl;
    printArray(a);

    if (m > lo)
    {
        qs(a, lo, m - 1);
    }
    if (m < hi)
    {
        qs(a, m + 1, hi);
    }
}

int main(int argc, char **argv)
{
    // Read the numbers from file
    ifstream inFile(argv[1]);

    int n;
    vector<int> numbers;
    while (inFile >> n)
    {
        numbers.push_back(n);
    }

    printArray(numbers);
    //partition(numbers, 0, numbers.size() - 1, 7);
    qs(numbers, 0, numbers.size() - 1);
    printArray(numbers);

    return 0;
}
