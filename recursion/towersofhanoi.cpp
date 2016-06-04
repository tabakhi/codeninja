// 161. Towers of Hanoi
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

class namedStack : public stack<int> 
{
 public:
  namedStack(const string &name) : m_name(name) {}
  const string m_name;
};

void printStack(const namedStack &s)
{
    cout << "Contents of " << s.m_name << endl;

    namedStack tmpStack = s;
    while (tmpStack.empty() == false)
    {
        int curr = tmpStack.top();
        tmpStack.pop();

        cout << curr << " ";
    }

    cout << endl;
}

void printThreeStacks(namedStack &first, namedStack &second, namedStack &third)
{
    if (first.m_name == "p1")
    {
        printStack(first);
    }
    else if (second.m_name == "p1")
    {
        printStack(second);
    }
    else 
    {
        printStack(third);
    }

    if (first.m_name == "p2")
    {
        printStack(first);
    }
    else if (second.m_name == "p2")
    {
        printStack(second);
    }
    else 
    {
        printStack(third);
    }

    if (first.m_name == "p3")
    {
        printStack(first);
    }
    else if (second.m_name == "p3")
    {
        printStack(second);
    }
    else 
    {
        printStack(third);
    }

}

void moveTwoRings(namedStack &first, namedStack &second, namedStack &third)
{
    int one = first.top();
    first.pop();

    assert(third.empty() || (third.top() > one));
    third.push(one);

    int two = first.top();
    first.pop();

    assert(second.empty() || (second.top() > two));
    second.push(two);

    one = third.top();
    third.pop();

    assert(second.empty() || (second.top() > one));
    second.push(one);
}

void moveRings(namedStack &first, namedStack &second, namedStack &third, int n)
{
    cout << __FUNCTION__ << " begin n = " << n << ", "
    << first.m_name << " " << second.m_name << " " << third.m_name 
    << endl;

    printThreeStacks(first, second, third);

    if (n == 2)
    {
        moveTwoRings(first, second, third);
        printThreeStacks(first, second, third);
        cout << __FUNCTION__ << " end n = " << n << endl;
        return;
    }

    moveRings(first, third, second, n - 1);

    int curr = first.top();
    first.pop();

    assert(second.empty() || (curr < second.top()));
    second.push(curr);

    moveRings(third, second, first, n - 1);

    cout << __FUNCTION__ << " end n = " << n << endl;
    printThreeStacks(first, second, third);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Please specify number of rings" << endl;
        return -1;
    }

    int n = atoi(argv[1]);

    namedStack p1("p1");
    namedStack p2("p2");
    namedStack p3("p3");

    for (int i = n; i >= 1; i--)
    {
        p1.push(i);
    }

    printStack(p1);
    moveRings(p1, p2, p3, p1.size());

    cout << "The stacks after the move" << endl;

    printStack(p1);
    printStack(p2);
    printStack(p3);

    return 0;
}

