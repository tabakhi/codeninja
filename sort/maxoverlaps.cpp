// 14.5: Render a calendar
// The textbooks solution does a sort and stores a bool to 
// break ties if the same value has a start and end
// My solution uses a map and a heap but the storage and time 
// complexity is thes same.
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

using namespace std;

size_t findMaxOverlaps(const vector< pair<int, int> > &intervals)
{
    map<int, int> iMap;

    // Add to map with start time as key
    for (size_t i = 0; i < intervals.size(); i++)
    {
        iMap[intervals[i].first] = intervals[i].second;
    }

    // A heap of all the end times
    priority_queue<int, vector<int>, greater<int> > ends;

    size_t iMax = 0;
    size_t nMax = 0;

    for (std::map<int, int>::iterator it=iMap.begin(); it!=iMap.end(); ++it)
    {
        if (ends.empty())
        {
            iMax = 1;
            ends.push(it->second);
        }
        else if (it->first <= ends.top())
        {
            ++iMax;
            ends.push(it->second);
        }
        else
        {
            while (!ends.empty() && ends.top() < it->first)
            {
                ends.pop();
                --iMax;
            }
            ends.push(it->second);
            ++iMax;
        }

        if (iMax >= nMax)
        {
            cout << "Adding " << it->first << ", " << it->second << 
                " makes the current largest overlap" << endl;
        }
        nMax = std::max(nMax, iMax);
        cout << iMax << " " << nMax << endl;
    }

    return nMax;
}

int main(int argc, char **argv)
{
    vector< pair<int, int> > intervals;
    intervals.push_back(pair<int, int>(1, 5));
    intervals.push_back(pair<int, int>(2, 4));
    intervals.push_back(pair<int, int>(5, 8));
    intervals.push_back(pair<int, int>(6, 10));
    intervals.push_back(pair<int, int>(7, 9));
    intervals.push_back(pair<int, int>(10, 13));
    intervals.push_back(pair<int, int>(15, 18));

    for (size_t i = 0; i < intervals.size(); i++)
    {
        cout << intervals[i].first << ", " << intervals[i].second << endl;
    }

    cout << findMaxOverlaps(intervals) << endl;
    return 0;
}

