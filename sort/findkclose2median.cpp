// Problem 11.8
// Find the k elements closest to the median
// Closeness is measured by the distance of a number 
// from the median
// E.g. if median = 100, x = 95, distance = 5
#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class dist
{
public:
    size_t d;
    size_t index; // index into original array

    dist& operator =(const dist& rhs)
    {
        if (this != &rhs)
        {
            d = rhs.d;
            index = rhs.index;
        }
        return *this;
    }

};

std::ostream& operator <<(std::ostream &os, const dist &obj)
{
    return os << "{" << obj.d << "," << obj.index << "}";
}

bool 
operator <(const dist &lhs, const dist &rhs)
{
    return lhs.d < rhs.d;
}

template <typename T>
size_t partition(vector<T> &a, size_t left, size_t right, size_t pivotindex)
{
    cout << __func__ << " left = " << left << " " << "right = "
    << right << " pivotindex = " << pivotindex << 
    " pivot element = " << a[pivotindex] << endl;

    T pivotval = a[pivotindex];

    // swap pivotval with right most value
    T tmp = a[right];
    a[right] = pivotval;
    a[pivotindex] = tmp;

    size_t si = left; // store index
    for (int i = left; i <= right-1; i++)
    {
        if (a[i] < pivotval)
        {
            T tmp = a[si];
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

void printA(const vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

void printD(const vector<dist> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i].d << "," << arr[i].index << " ";
    }

    cout << endl;
}

template<typename T>
void printArr(const vector<T> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << "\t";
    }
    cout << endl;
}

// find the kth element
template<typename T>
size_t quickselect(vector<T> &a, size_t left, size_t right, size_t k)
{
    cout << __func__ << " left = " << left << " " << "right = "
    << right << " k = " << k << endl;

    if (left == right)
    {
        //return a[left];
        return left;
    }

    int pivotindex = left + (rand() % (right - left + 1));

    size_t index = partition(a, left, right, pivotindex);

    cout << "After that array contents are: " << endl;
    printArr(a);

    if (index == k)
    {
        //return a[index];
        return index;
    }
    else if (index > k)
    {
        return quickselect(a, left, index-1, k);
    }
    else
    {
        return quickselect(a, index+1, right, k);
    }

}

// Create a vector of distances from the median
void makeDistanceArray(vector<int> &a, vector<dist> &dArr, int median)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        size_t distance = abs(a[i] - median);
        dist curr = {distance, i};
        dArr.push_back(curr);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " list.txt k" << endl;
        return -1;
    }

    // Read the numbers from file
    ifstream inFile(argv[1]);

    // Find the k elements closest to the median
    uint32_t k = atoi(argv[2]);

    int n;
    vector<int> numbers, numbers2;
    while (inFile >> n)
    {
        numbers.push_back(n);
    }

    printA(numbers);
    numbers2 = numbers;

    // First find the median
    // For even sized list this will use the higher number
    // E.g. if list size = 10, m = 5
    size_t m = numbers.size()/2;

    int medianIndex = quickselect(numbers, 0, numbers.size() - 1, m);

    cout << "The median is " << numbers[medianIndex] << endl;
    printA(numbers);

    vector<dist> distances;
    makeDistanceArray(numbers2, distances, numbers[medianIndex]);
    cout << "Printing the distances array" << endl;
    printD(distances);

    size_t kIndex = quickselect(distances, 0, distances.size() - 1, k-1);
    printD(distances);

    cout << "The " << k << " numbers closest to the median (including itself)"
        << " are " << endl;
    for (size_t i = 0; i <= kIndex; i++)
    {
        cout << numbers2[distances[i].index] << "\t";
    }
    cout << endl;

    return 0;
}
