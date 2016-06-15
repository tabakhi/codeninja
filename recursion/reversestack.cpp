// http://www.geeksforgeeks.org/reverse-a-stack-using-recursion/
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

void printStack(const stack<int> &s)
{
    stack<int> tmpStack = s;
    while (tmpStack.empty() == false)
    {
        int curr = tmpStack.top();
        tmpStack.pop();

        cout << curr << " ";
    }

    cout << endl;
}

void insert(stack<int> &s, int val)
{
    cout << __FUNCTION__ << " stack size = " << s.size() 
        << " " << " val = " << val << endl;

    if (s.empty())
    {
        s.push(val);
    }
    else
    {
        cout << __FUNCTION__ << " top = " << s.top() 
            << " val = " << val << endl;

        int top = s.top();
        s.pop();
        insert(s, val);
        s.push(top);
    }
}

void reverseStack(stack<int> &s)
{
    cout << __FUNCTION__ << " begin on stack size = " << s.size() 
        << endl;

    if (s.empty())
    {
        cout << __FUNCTION__ << " reached base case stack size = 0" 
            << endl;
        return;
    }

    int curr = s.top();
    s.pop();

    reverseStack(s);

    insert(s, curr);

    cout << __FUNCTION__ << " finished on stack size = " << s.size() 
        << endl;

    cout << "Partially sorted stack looks like this " << endl;
    printStack(s);
}

int main(int argc, char **argv)
{
    // Read the numbers from file
    ifstream inFile(argv[1]);

    int n;
    stack<int> numbers;
    while (inFile >> n)
    {
        numbers.push(n);
    }

    printStack(numbers);
    reverseStack(numbers);
    printStack(numbers);

    return 0;
}

