#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <queue>
#include <algorithm>
#include <string.h>
#include <assert.h>

using namespace std;

void printArray(const vector<pair<int, int> > &arr)
{
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout << "[" << arr[i].first << " " << arr[i].second << "]" << endl;
    }

    cout << endl;
}

void appendA(const vector< pair<int, int> > &a,
        size_t start, size_t end,
        vector< pair<int, int> > &results)
{
    for (size_t i = start; i < end; i++)
    {
        results.push_back(a[i]);
    }
}

void makeUnion(const vector< pair<int, int> > &a, 
        const pair<int, int> &g,
        vector< pair<int, int> > &result)

{
    if (a.size() == 0)
    {
        result.push_back(g);
    }
    // E.g. g = [5, 100] a0 = 7, 11 a(n-1) = [95, 99] 
    else if (g.first <= a[0].first && g.second >= a[a.size()-1].second)
    {
        result.push_back(g);
    }
    // E.g. g = [7, 10], a = [12, 15], ....
    else if (g.second < a[0].first)
    {
        result.push_back(g);
        appendA(a, 0, a.size(), result);
    }
    // E.g. g = [7, 12], a = [12, 15], ....
    // Union = [7, 15], a[1], a[2], ...
    else if (g.second == a[0].first)
    {
        pair<int, int> g2(g.first, a[0].second);
        result.push_back(g2);
        appendA(a, 1, a.size(), result);
    }
    // E.g. a = .... [75, 90] g = [90, 99]
    // Union = a[0], a[1], ... a[n-2], [75, 99]
    else if (g.first == a[a.size()-1].second)
    {
        pair<int, int> g2(a[a.size()-1].first, g.second);
        appendA(a, 0, a.size()-1, result);
        result.push_back(g2);
    }
    // E.g. a = .... [75, 90] g = [93, 99]
    else if (g.first > a[a.size()-1].second)
    {
        appendA(a, 0, a.size(), result);
        result.push_back(g);
    }
    else
    {
        bool foundStart = false;
        bool foundEnd = false;
        bool startIntersects = false;
        bool endIntersects = false;
        size_t start = 0;
        size_t end = 0;

        pair <int, int> g2;

        for (size_t i = 0; i < a.size(); i++)
        {
            if (!foundStart && g.first < a[i].first)
            {
                foundStart = true;
                start = i;
            }

            if (!foundStart && g.first == a[i].first)
            {
                foundStart = true;
                startIntersects = true;
                start = i;
            }

            if (!foundStart && g.first < a[i].second)
            {
                foundStart = true;
                startIntersects = true;
                start = i;
            }

            if (!foundStart && g.first == a[i].second)
            {
                foundStart = true;
                startIntersects = true;
                start = i;
            }

            if (foundStart && !foundEnd && g.second < a[i].first)
            {
                foundEnd = true;
                end = i;
            }

            if (foundStart && !foundEnd && g.second == a[i].first)
            {
                foundEnd = true;
                endIntersects = true;
                end = i;
            }

            if (foundStart && !foundEnd && g.second < a[i].second)
            {
                foundEnd = true;
                endIntersects = true;
                end = i;
                end = i;
            }

            if (foundStart && !foundEnd && g.second == a[i].second)
            {
                foundEnd = true;
                endIntersects = true;
                end = i;
                end = i;
            }
        } // for loop

        // now combine
        for (size_t i = 0; i < start; i++)
        {
            result.push_back(a[i]);
        }

        if (startIntersects)
        {
            g2.first = a[start].first;
        }
        else
        {
            g2.first = g.first;
        }

        if (endIntersects)
        {
            g2.second = a[end].second;
            ++end;
        }
        else
        {
            g2.second = g.second;
        }

        result.push_back(g2);

        for (size_t i = end; i <= a.size() - 1 && foundEnd; i++)
        {
            result.push_back(a[i]);
        }
    }

}

int main(int argc, char **argv)
{
    ifstream inFile( argv[1] );

    int x = atoi(argv[2]);
    int y = atoi(argv[3]);

    pair<int, int> g(x, y);

    vector< pair<int, int> > intervals;
    
    pair<int, int> interval;
    int n; 
    size_t i = 0;

    // Format of the file should be:
    // 1 2
    // 3 4
    // 5 6
    // ...
    while (inFile >> n)
    {
        if (++i % 2)
        {
            interval.first = n;
        }
        else
        {
            interval.second = n;
            intervals.push_back(interval);
        }
    }

    assert (i % 2 == 0);

    cout << "The intervals to be merged are: " << endl;
    printArray(intervals);

    vector< pair <int, int> > result;
    makeUnion(intervals, g, result);

    cout << "The intervals after merge are: " << endl;
    printArray(result);
    return 0;
}

