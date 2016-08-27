// 6.22: Print a 2D array in spiral order
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>

using namespace std;

void printA(const vector< vector<int> > &a, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << a[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printSpiral(const vector< vector<int> > &a, size_t n)
{
    int n2 = 0;
    int startRow = 0;
    int endRow = n-1;
    
    int startCol = 0;
    int endCol = n-1;

    while (1)
    {
        cout << "start row = " << startRow << endl;
        cout << "start col = " << startCol << endl;
        cout << "end row = " << endRow << endl;
        cout << "end col = "  << endCol << endl;

        // print row from left to right
        for (int c = startCol; c < endCol && n2 < n*n; c++)
        {
            cout << a[startRow][c] << " ";
            ++n2;
        }
        cout << endl;

        if (n2 >= n*n)
        {
            break;
        }

        // print col from top to bottom
        for (int r = startRow; r < endRow && n2 < n*n; r++)
        {
            cout << a[r][endCol] << " ";
            ++n2;
        }
        cout << endl;

        if (n2 >= n*n)
        {
            break;
        }

        // print row from right to left
        for (int c = endCol; c > startCol && n2 < n*n; c--)
        {
            cout << a[endRow][c] << " ";
            ++n2;
        }
        cout << endl;

        if (n2 >= n*n)
        {
            break;
        }

        // print col from bottom to top
        for (int r = endRow; r > startRow && n2 < n*n; r--)
        {
            cout << a[r][startCol] << " ";
            ++n2;
        }
        cout << endl;

        if (n2 >= n*n)
        {
            break;
        }
        ++startRow;
        ++startCol;
        --endRow;
        --endCol;
       
        if (n % 2 && n2 == n*n - 1)
        {
            break;
        }

    }

    if (n % 2)
    {
        cout << a[startRow][startCol] << endl;
    }

}


int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "Usage:  " << argv[0] << " filename n" << endl;
        return -1;
    }

    // Read the numbers from file
    ifstream inFile(argv[1]);

    // size of the array (nxn)
    int n = atoi(argv[2]);

    vector< vector<int> > a(n);

    int i = 0;
    int j = 0;
    int x = 0;
    while (inFile >> x)
    {
        a[i].push_back(x);
        if (++j == n)
        {
            j = 0;
            i++;
        }
    }

    printA(a, n);

    printSpiral(a, n);
    return 0;
}
