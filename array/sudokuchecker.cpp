// 6.21: Sudoku checker
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>

using namespace std;

void printA(const int a[][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << a[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool checkRows(const int a[][9])
{
    for (int i = 0; i < 9; i++)
    {
        int map[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int j = 0; j < 9; j++)
        {
            int val = a[i][j];
            if (val && map[val-1] == val)
            {
                cout << "Element " << val << " at index " << i << "," <<
                j << " already exists" << endl;
                return false;
            }
            else
            {
                map[val-1] = val;
            }
        }
    }
}

bool checkCols(const int a[][9])
{
    for (int j = 0; j < 9; j++)
    {
        int map[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 9; i++)
        {
            int val = a[i][j];
            if (val && map[val-1] == val)
            {
                cout << "Element " << val << " at index " << i << "," <<
                j << " already exists" << endl;
                return false;
            }
            else
            {
                map[val-1] = val;
            }
        }
    }
}

bool checkGrids(const int a[][9])
{
    for (int sq = 0; sq < 9; sq++)
    {
        int map[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int iBegin = (sq/3)*3;
        int jBegin = (sq%3)*3; 

        for (int i = iBegin; i < iBegin+3; i++)
        {
            for (int j = jBegin; j < jBegin+3; j++)
            {
                int val = a[i][j];
                if (val && map[val-1] == val)
                {
                    cout << "Element " << val << " at index " << i << "," <<
                        j << " already exists" << endl;
                    return false;
                }
                else if (val)
                {
                    map[val-1] = val;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    int a[9][9];
    // Read the numbers from file
    ifstream inFile(argv[1]);

    int i = 0;
    int j = 0;
    int n;
    while (inFile >> n)
    {
        a[i][j++] = n;
        if (j == 9)
        {
            j = 0;
            i++;
        }
    }

    printA(a);

    checkRows(a);
    checkCols(a);
    checkGrids(a);
    return 0;
}
