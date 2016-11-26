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

class line 
{
 public:
  int k1; // start x or y
  int k2; // end x or y
  int m; // x or y coord 
  int type; // 1 = horiz. 2 = verti.

  line(int ak1, int ak2, int am, int atype) :
  k1(ak1),
  k2(ak2),
  m(am),
  type(atype)
  {}
};

class event
{
 public:
  line *pLine; 
  int x; // x position
  int type; // 1 = horiz. 2 = vertic.
  bool start; // start of line or end (applies to horizonal lines)

  void init(line *line, int x, int type, bool astart);
};

void event::init(line *line, int ax, int atype, bool astart)
{
    pLine = line;
    x = ax;
    type = atype;
    start = astart;
}

void addEvents(line *line, vector<event> &eventArr)
{
    if (line->type == 1)
    {
        event e1;
        e1.init(line, line->k1, line->type, true);

        event e2;
        e2.init(line, line->k2, line->type, false);

        eventArr.push_back(e1);
        eventArr.push_back(e2);
    }
    else
    {
        event e;
        e.init(line, line->m, line->type, false);
        eventArr.push_back(e);
    }
}

bool compareEvents(const event &e1, const event &e2)
{
    if (e1.type != e2.type)
    {
        if (e1.x != e2.x)
            return e1.x < e2.x;
        else if (e1.type == 1 && e1.start)
        {
            return true;
        }
        else if (e1.type == 1 && !e1.start)
        {
            return false;
        }
        else if (e2.type == 1 && e2.start)
        {
            return true;
        }
        else if (e2.type == 1 && !e2.start)
        {
            return false;
        }
    }
    else
    {
        return e1.x < e2.x;
    }
}

int main(int argc, char **argv)
{
    line l1(1, 5, 1, 1); // h [1,5] at y=1
    line l2(2, 4, 2, 1); // h [2,4] at y=2

    line l3(2, 5, 3, 2); // v [2,5] at x=3

    line l4(6, 9, 4, 1); // h [6, 9] at y=4
    line l5(0, 7, 8, 2); // v [0, 7] at x=8
    line l6(0, 7, 10, 2); // v [0, 7] at x=10

    line l7(8, 10, 3, 1); // h [8, 10] at y = 3

    vector<event> eventArr;

    addEvents(&l1, eventArr);
    addEvents(&l2, eventArr);
    addEvents(&l3, eventArr);
    addEvents(&l4, eventArr);
    addEvents(&l5, eventArr);
    addEvents(&l6, eventArr);
    addEvents(&l7, eventArr);

    sort(eventArr.begin(), eventArr.end(), compareEvents);

    // A map of all horizontal lines by their y-coordinate
    map<int, line *> pq;

    for (size_t i = 0; i < eventArr.size(); i++)
    {
        // horizontal line
        if (eventArr[i].type == 1)
        {
            // starts a line
            if (eventArr[i].start)
            {
                cout << "Adding horizontal line with x-coord " <<
                    eventArr[i].x << endl;

                pq[eventArr[i].pLine->m] = eventArr[i].pLine;
            }
            else
            {
                cout << "Removing horizontal line with x-coord " <<
                    eventArr[i].x << endl;

                map<int, line *>::iterator it = 
                    pq.find(eventArr[i].pLine->m);
                assert(it != pq.end());

                pq.erase(it);
            }
        }
        else // vertical line
        {
            cout << "Processing vertical line " << 
                eventArr[i].pLine->k1 << "," << eventArr[i].pLine->k2 <<
                " at x = " << eventArr[i].pLine->m << endl;

            int yl = eventArr[i].pLine->k1;
            int yh = eventArr[i].pLine->k2;

            // Find all lines between [yl, yh]
            map<int, line *>::iterator it1 = pq.lower_bound(yl);
            map<int, line *>::iterator it2 = pq.upper_bound(yh);

            int i = 0;
            for ( map<int, line *>::iterator it = it1; it != it2; it++)
            {
                if (i++ == 0)
                {
                    cout << "Intersects with horizontal lines: " << endl;
                }
                cout << it->second->k1 << " " << it->second->k2 << endl;
            }

            cout << "done processing vertical line" << endl;
        }
    }

    return 0;
}

