// Fibonacci sequence
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

using namespace std;

int fib(int n)
{
    if (n <= 2)
    {
        return 1;
    }

    int prev1 = 1; // f(n-1)
    int prev2 = 1; // f(n-2)

    int sum = 0;
    for (int i = 3; i <= n; i++)
    {
        sum = prev1 + prev2;

        prev2 = prev1;
        prev1 = sum;
    }

    return sum;
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Please specify n" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int sum = fib(n);

    cout << "fib(" << n << ")" << " = " << sum << endl;
    return 0;
}

