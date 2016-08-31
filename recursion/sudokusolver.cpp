// 16.10 Sudoku solver
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <assert.h>

using namespace std;
const int N = 9;

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

void checkSubgrid(size_t i, size_t j, int *pSet,
                  vector< vector<int> > &a)
{
    size_t row = 0;
    size_t col = 0;
    if (i < 3)
        row = 0;
    else if (i < 6)
        row = 1;
    else
        row = 2;

    if (j < 3)
        col = 0;
    else if (j < 6)
        col = 1;
    else 
        col = 2;

    for (size_t si = row*3; si < row*3 + 3; si++)
    {
        for (size_t sj = col*3; sj < col*3 + 3; sj++)
        {
            if (a[si][sj])
            {
                pSet[a[si][sj]-1] = 0;
            }
        }
    }
}

void makePossible(vector< vector<int> > &a, 
                  vector < vector <int> > &possible)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (a[i][j] == 0)
            {
                int set[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                // Eliminate what is already in this col
                for (size_t k = 0; k < N; k++)
                {
                    if (a[k][j])
                    {
                        set[a[k][j] - 1] = 0;
                    }
                }

                // Eliminate what is already in this row
                for (size_t k = 0; k < N; k++)
                {
                    if (a[i][k])
                    {
                        set[a[i][k] - 1] = 0;
                    }
                }

                // Eliminate what is in this subgrid
                checkSubgrid(i, j, set, a);

                for (size_t k = 0; k < N; k++)
                {
                    if (set[k])
                    {
                        possible[i*N + j].push_back(set[k]);
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (a[i][j])
            {
                continue;
            }

            cout << "Possible values for " << "i = " << i <<
            " j = " << j << endl;

            for (size_t k = 0; k < possible[i*N + j].size(); k++)
            {
                cout << possible[i*N + j][k] << " ";
            }
            cout << endl;
        }
    }

}

bool check(vector< vector<int> > &a, size_t r, size_t c)
{
    // check row
    int set[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (size_t j = 0; j < N; j++)
    {
        if (a[r][j])
        {
            if (set[a[r][j] - 1])
            {
                return false;
            }
            set[a[r][j] - 1] = a[r][j];
        }
    }

    // check col
    for (size_t i = 0; i < N; i++)
    {
        set[i] = 0;
    }

    for (size_t i = 0; i < N; i++)
    {
        if (a[i][c])
        {
            if (set[a[i][c] - 1])
            {
                return false;
            }
            set[a[i][c] - 1] = a[i][c];
        }
    }

    // check subgrid
    r /= 3;
    c /= 3;

    for (size_t i = 0; i < N; i++)
    {
        set[i] = 0;
    }

    for (size_t i = r*3; i < r*3 + 3; i++)
    {
        for (size_t j = c*3; j < c*3; j++)
        {
            if (a[i][j])
            {
                if (set[a[i][j] - 1])
                {
                    return false;
                }
                set[a[i][j] - 1] = a[i][j];
            }
        }
    }

    return true;
}

bool checkFinal(vector< vector<int> > &a)
{
    // check rows
    for (size_t i = 0; i < N; i++)
    {
        int set[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (size_t j = 0; j < N; j++)
        {
            if (a[i][j])
            {
                ++set[a[i][j] - 1];
            }
        }

        for (size_t j = 0; j < N; j++)
        {
            if (set[j] != 1)
            {
                return false;
            }
        }
    }

    // check cols
    for (size_t j = 0; j < N; j++)
    {
        int set[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (size_t i = 0; i < N; i++)
        {
            if (a[i][j])
            {
                ++set[a[i][j] - 1];
            }
        }

        for (size_t i = 0; i < N; i++)
        {
            if (set[i] != 1)
            {
                return false;
            }
        }
    }

    // check subgrid
    for (size_t r = 0; r < 9; r += 3)
    {
        for (size_t c = 0; c < 9; c += 3)
        {
            int set[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

            for (size_t i = r; i < r + 3; i++)
            {
                for (size_t j = c; j < c + 3; j++)
                {
                    if (a[i][j])
                    {
                        ++set[a[i][j] - 1];
                    }
                }
            }

            for (size_t k = 0; k < N; k++)
            {
                if (set[k] != 1)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool solve(vector< vector<int> > &a, 
           vector < vector <int> > &possible,
           size_t r, size_t c)
{
    cout << "solve " << "r = " << r << " c = " << c << endl;

    if (c == 9)
    {
        c = 0;
        ++r;
    }

    if (r == 9)
    {
        return checkFinal(a);
    }

    // Search for the next empty cell starting at [r,c]
    if (a[r][c] == 0)
    {
        for (size_t k = 0; k < possible[r*N + c].size(); k++)
        {
            cout << "solving " << "r = " << r <<
                " c = " << c << " with " <<
                possible[r*N + c][k] << 
                endl;
            a[r][c] = possible[r*N + c][k];

            if (check(a, r, c) == false)
            {
                cout << "check failed, continuing" << endl;
                continue;
            }

            if (solve(a, possible, r, c+1))
            {
                return true;
            }
        }
        a[r][c] = 0;
    }
    else 
    {
        if (solve(a, possible, r, c+1))
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage:  " << argv[0] << " filename" << endl;
        return -1;
    }

    // Read the sudoku grid numbers from file
    ifstream inFile(argv[1]);

    vector< vector<int> > a(N);

    int x = 0;
    int i = 0;
    int j = 0;
    while (inFile >> x)
    {
        assert (x >= 0);
        assert (x < 10);
        a[i].push_back(x);
        if (++j == N)
        {
            j = 0;
            i++;
        }
    }

    printA(a, N);

    vector < vector <int> > possible(N*N);

    makePossible(a, possible);

    solve(a, possible, 0, 0);
    printA(a, N);

    return 0;
}

