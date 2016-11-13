// 14.1: Compute the intersection of two sorted arrays
// There should be no duplicates in the merged result
// Note: I am only implementing the solution where both
// array sizes are of the same magnitude
// If one is very small compared to the other, it is faster
// to do a binary search over the other
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

void readNumbers(vector<int> &x, const std::string &strFile)
{
    ifstream inFile(strFile.c_str());
    int n;
    while (inFile >> n)
    {
        x.push_back(n);
    }
}

void mergeCommon(const vector<int> &a, const vector<int> &b, vector<int> &c)
{
    size_t i = 0; // index in a
    size_t j = 0; // index in b

    while (i < a.size() && j < b.size())
    {
        cout << "i = " << i << " j = " << j << endl;

        if (i > 0 && a[i] == a[i-1])
        {
            cout << "Skipping i = " << i << endl;
            ++i;
            continue;
        }

        if (j > 0 && b[j] == b[j-1])
        {
            cout << "Skipping j = " << j << endl;
            ++j;
            continue;
        }

        if (b[j] == a[i])
        {
            c.push_back(b[j]);
            ++i;
            ++j;
        }
        else if (b[j] < a[i])
        {
            ++j;
        }
        else
        {
            ++i;
        }
    }

}

int main(int argc, char **argv)
{
    vector<int> a, b, c;

    // Read the numbers from file
    readNumbers(a, argv[1]);
    readNumbers(b, argv[2]);

    mergeCommon(a, b, c);
    printArray(c);

    return 0;
}

