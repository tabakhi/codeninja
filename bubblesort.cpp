#include <climits>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printArray(const vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << "\t";
    }

    cout << endl;
}

void bubblesort(vector<int> &a)
{
    // Each iteration we sort the i'th element
    for(int i = 0; i < a.size(); i++)
    {
        cout << "Inserting the " << i << " element: "
        << a[i] << " in it's proper position" << endl;

        int storeindex = -1;

        for (int j = i - 1; j >= 0; j--)
        {
            cout << "Comparing against the " << j << " element: "
                << a[j] << endl;

            if (a[i] < a[j])
            {
                storeindex = j;
            }
        }

        cout << "storeindex = " << storeindex << endl;

        if (storeindex != -1)
        {
            int tmp = a[i];
            for (int j = i; j > storeindex; j--)
            {
                a[j] = a[j-1];
            }

            a[storeindex] = tmp;
        }
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
    bubblesort(numbers);
    printArray(numbers);

    return 0;
}

