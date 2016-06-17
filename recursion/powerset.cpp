// Print the power set of the given numbers
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream> // std::ostringstream
#include <vector>

using namespace std;

void printArray(const vector<int> &s)
{
    for (size_t i = 0; i < s.size(); i++)
    {
        cout << s[i] << " ";
    }

    cout << endl;
}

void printPowerSet(vector<int> &s, ostringstream &str, int lastIndex)
{
    cout << __FUNCTION__ << " beginning on last index = " << lastIndex 
        << endl;

    if (lastIndex == static_cast<int>(s.size()))
    {
        return;
    }

    for (size_t i = lastIndex; i < s.size(); i++)
    {
        ostringstream str2(str.str(), ostringstream::ate);
        str2 << s[i];
        cout << str2.str() << endl;

        str2 << ",";
        printPowerSet(s, str2, i + 1);
    }

    cout << __FUNCTION__ << " ending on last index = " << lastIndex << endl;
}

int main(int argc, char **argv)
{
    vector<int> numbers;

    for (int i = 1; i < argc; i++)
    {
        numbers.push_back(atoi(argv[i]));
    }

    ostringstream str;
    printPowerSet(numbers, str, 0);

    return 0;
}

