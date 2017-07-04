// 5.13 Check if rectangles intersect
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

int
getX(int rx, int rw, int sx, int sw)
{
  int x = 0;
  if (rx <= sx && sx < rx + rw)
  {
    if (sx + sw < rx + rw)
    {
      x = sw;
    }
    else if (sx + sw >= rx + rw)
    {
      x = rx + rw - sx;
    }
  }

  return x;
}

int
getY(int ry, int rh, int sy, int sh)
{
  int y = 0;
  if (ry <= sy && sy < ry + rh)
  {
    if (sy + sh < ry + rh)
    {
      y = sh;
    }
    else if (sy + sh >= ry + rh)
    {
      y = ry + rh - sy;
    }
  }

  return y;
}

int main(int argc, char **argv) {

    if (argc != 9)
    {
      cerr << "Need 8 arguments" << endl;
      return 1;
    }

    int rx = atoi(argv[1]);
    int ry = atoi(argv[2]);
    int rw = atoi(argv[3]);
    int rh = atoi(argv[4]);

    int sx = atoi(argv[5]);
    int sy = atoi(argv[6]);
    int sw = atoi(argv[7]);
    int sh = atoi(argv[8]);

    cout << "rx = " << rx << endl;
    cout << "rw = " << rw << endl;
    cout << "ry = " << ry << endl;
    cout << "rh = " << rh << endl;

    cout << "sx = " << sx << endl;
    cout << "sw = " << sw << endl;
    cout << "sy = " << sy << endl;
    cout << "sh = " << sh << endl;

    int x = 0;
    int y = 0;
    if (rx < sx)
    {
        x = getX(rx, rw, sx, sw);
    }
    else
    {
      x = getX(sx, sw, rx, rw);
    }

    if (ry < sy)
    {
        y = getY(ry, rh, sy, sh);
    }
    else
    {
        y = getY(sy, sh, ry, rh);
    }

    cout << x*y << endl;
    return 0;
}
