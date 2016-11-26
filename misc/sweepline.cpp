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
  int type; // 1 = horiz. 2 = vertic.
  bool start; // start of line or end (applies to horizonal lines)

  void init(line *line, int type, bool astart);
};

void event::init(line *line, int atype, bool astart)
{
    pLine = line;
    type = atype;
    start = astart;
}

int main(int argc, char **argv)
{
    line l1(1, 5, 1, 1); // h [1,5] at y=1
    line l2(2, 4, 2, 1); // h [2,4] at y=2

    line l3(2, 5, 3, 2); // v [2,5] at x=3

    line l4(6, 9, 4, 1); // h [6, 9] at y=4
    line l5(0, 7, 8, 2); // v [0, 7] at x=8
    line l6(0, 7, 10, 2); // v [0, 7] at x=10

    // manually sorting events
    int nEvents = 9;
    event *pEvents = new event[nEvents];
    pEvents[0].init(&l1, 1, true);
    pEvents[1].init(&l2, 1, true);
    pEvents[2].init(&l3, 2, false);
    pEvents[3].init(&l2, 1, false);
    pEvents[4].init(&l1, 1, false);
    pEvents[5].init(&l4, 1, true);
    pEvents[6].init(&l5, 2, false);
    pEvents[7].init(&l4, 1, false);
    pEvents[8].init(&l6, 2, false);

    // A map of all horizontal lines by their y-coordinate
    map<int, line *> pq;

    for (int i = 0; i < nEvents; i++)
    {
        // horizontal line
        if (pEvents[i].type == 1)
        {
            // starts a line
            if (pEvents[i].start)
            {
                pq[pEvents[i].pLine->m] = pEvents[i].pLine;
            }
            else
            {
                map<int, line *>::iterator it = 
                    pq.find(pEvents[i].pLine->m);
                assert(it != pq.end());

                pq.erase(it);
            }
        }
        else // vertical line
        {
            cout << "Processing vertical line " << 
                pEvents[i].pLine->k1 << "," << pEvents[i].pLine->k2 <<
                " at x = " << pEvents[i].pLine->m << endl;

            int yl = pEvents[i].pLine->k1;
            int yh = pEvents[i].pLine->k2;

            // Find all lines between [yl, yh]
            map<int, line *>::iterator it1 = pq.lower_bound(yl);
            map<int, line *>::iterator it2 = pq.upper_bound(yh);

            for ( map<int, line *>::iterator it = it1; it != it2; it++)
            {
                cout << it->second->k1 << " " << it->second->k2 << endl;
            }

            cout << "done processing vertical line" << endl;
        }
    }

    delete [] pEvents;
    return 0;
}

