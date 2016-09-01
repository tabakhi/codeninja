// 6.23 Rotate a 2D array
#include <vector>
#include <iostream>
#include <iomanip>
#include <inttypes.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void printAw(const vector< vector<int> > &a, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << setw(2) << a[i][j];
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void rotateCols(vector< vector<int> > &a, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n/2; j ++)
        {
            std::swap(a[i][j], a[i][n-1-j]);
        }
    }
}

// for a nxn array m = number of diagonals
void rotateDiag(vector< vector<int> > &a, size_t n)
{
    size_t sr = 0;
    size_t sc = 0;
    size_t dr = 0;
    size_t dc = 0;

    size_t elems = 0; // # of elements to swap on this diagonal
    size_t m = 2*n - 1;

    for (size_t k = 1; k <= m; k++)
    {
        if (k <= n)
        {
            elems = k/2;
        }
        else if (k > n && k%2)
        {
            --elems;
        }

        cout << "k = " << k << " " <<
            "elements to swap = " << elems 
            << endl;

        size_t lsr = sr;
        size_t lsc = sc;
        size_t ldr = dr;
        size_t ldc = dc;

        int elems2 = static_cast<int>(elems);
        while (elems2-- > 0)
        {
            std::swap(a[lsr][lsc], a[ldr][ldc]);
            ++lsr;
            --lsc;
            --ldr;
            ++ldc;
        }

        if (++sc == n)
        {
            sc = n - 1;
            ++sr;
        }

        if (++dr == n)
        {
            dr = n-1;
            ++dc;
        }

    }

}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "Usage:  " << argv[0] << " filename" << endl;
        return -1;
    }

    // Read the 2D array numbers from file
    ifstream inFile(argv[1]);

    size_t n = atoi(argv[2]);

    vector< vector<int> > a(n);

    int x = 0;
    int i = 0;
    int j = 0;
    while (inFile >> x)
    {
        a[i].push_back(x);
        if (++j == n)
        {
            j = 0;
            i++;
        }
    }

    printAw(a, n);
    rotateDiag(a, n);
    printAw(a, n);
    rotateCols(a,n);
    printAw(a, n);
    return 0;
}

