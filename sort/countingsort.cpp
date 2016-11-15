#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string.h>

using namespace std;

void printArray(const vector<int> &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

void countSort(vector<int> &input)
{
    // Calculate the min and max of the range so that we can allocate the array for histogram
    int min = *std::min_element(input.begin(), input.end());
    int max = *std::max_element(input.begin(), input.end());

    // Compute histogram
    int *count = new int[max - min + 1];
    memset(count, 0, sizeof(int)*(max - min + 1));

    for (size_t i = 0; i < input.size(); i++)
    {
        ++count[input[i] - min];
    }

    // Calculate prefix sum
    int total = 0;
    for (int i = 0; i < (max - min + 1); i++)
    {
        int curr = count[i];
        count[i] = total;
        total += curr;
    }

    vector<int> output(input.size());
    for (size_t i = 0; i < input.size(); i++)
    {
        output[count[input[i] - min]++] = input[i];
    }

    delete [] count;
    input = output;
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
    countSort(numbers);
    printArray(numbers);

    return 0;
}

