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

void sort3way(vector<int> &a, vector<int> &b, vector<int> &c, vector<int> &merged)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    for (size_t m = 0; m < a.size() + b.size() + c.size(); m++)
    {
        bool haveA = (i < a.size());
        bool haveB = (j < b.size());
        bool haveC = (k < c.size());

        if (haveA && haveB && haveC)
        {
            if (a[i] <= b[j] && a[i] <= c[k])
            {
                merged.push_back(a[i++]);
            }
            else if (b[j] <= a[i] && b[j] <= c[k])
            {
                merged.push_back(b[j++]);
            }
            else if (c[k] <= a[i] && c[k] <= b[j])
            {
                merged.push_back(c[k++]);
            }
        }
        else if (haveA && haveB)
        {
            if (a[i] <= b[j])
            {
                merged.push_back(a[i++]);
            }
            else
            {
                merged.push_back(b[j++]);
            }
        }
        else if (haveB && haveC)
        {
            if (b[j] <= c[k])
            {
                merged.push_back(b[j++]);
            }
            else
            {
                merged.push_back(c[k++]);
            }
        }
        else if (haveA && haveC)
        {
            if (a[i] <= c[k])
            {
                merged.push_back(a[i++]);
            }
            else
            {
                merged.push_back(c[k++]);
            }
        }
        else if (haveA)
        {
            merged.push_back(a[i++]);
        }
        else if (haveB)
        {
            merged.push_back(b[j++]);
        }
        else 
        {
            merged.push_back(c[k++]);
        }
    }

}

int main(int argc, char **argv)
{
    vector<int> a, b, c, merged;

    // Read the numbers from file
    readNumbers(a, argv[1]);
    readNumbers(b, argv[2]);
    readNumbers(c, argv[3]);

    sort3way(a, b, c, merged);
    printArray(merged);

    return 0;
}

