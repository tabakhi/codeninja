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

void bottomup(vector<int> &a)
{
    size_t n = a.size();

    size_t width = 0;
    for (width = 1; width < n; width *= 2)
    {
        cout << "Merging sublists of width = " << width << endl;

        for (size_t i = 0; i < n; i += width*2)
        {
            size_t begin = i;
            size_t mid = i + width;
            size_t end = std::min(i + width*2, n);
            cout << "i = " << i <<
            " begin = " << begin <<
            " mid = " << mid <<
            " end = " << end << 
            endl;

            tdmerge(a, begin, mid, end);
        }

        cout << "List after sorting sublists of width = " << width << endl;
        printArray(a);
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
    //tdsort(numbers, 0, numbers.size());
    bottomup(numbers);
    printArray(numbers);

    return 0;
}

