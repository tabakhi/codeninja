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

void tdmerge(vector<int> &a, size_t begin, size_t mid, size_t end)
{
    vector<int> b;

    size_t i = begin;  // index into the 1st list
    size_t j = mid;    // index into the 2nd list

    while (i < mid && j < end)
    {
        b.push_back((a[i] < a[j]) ? a[i++] : a[j++]);
    }

    if (i == mid)
    {
        while (j < end)
        {
            b.push_back(a[j++]);
        }
    }
    else if (j == end)
    {
        while (i < mid)
        {
            b.push_back(a[i++]);
        }
    }

    assert(b.size() == (end - begin));

    for (size_t k = 0; k < b.size(); k++)
    {
        a[begin + k] = b[k];
    }
        
}

void tdsort(vector<int> &a, size_t begin, size_t end)
{
    cout << __FUNCTION__ << " invoked on begin = " << begin 
        << " end = " << end << endl;

    if (end - begin == 1)
    {
        return;
    }

    size_t mid = (end + begin) / 2;
    tdsort(a, begin, mid);
    tdsort(a, mid, end);
    tdmerge(a, begin, mid, end);

    cout << __FUNCTION__ << " finished begin = " << begin 
        << " end = " << end << endl;

    cout << "Partially sorted array looks like this " << endl;
    for (size_t i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
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
    tdsort(numbers, 0, numbers.size());
    printArray(numbers);

    return 0;
}

