// Print the last n lines of a file
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include <fstream>      // std::ifstream
#include <vector>

using namespace std;

int getnumlines(const char *buf, const int sz)
{
  int lines = 0;
  for (int i = sz - 1; i >= 0; i--)
  {
    if (buf[i] == '\n')
      ++lines;
  }

  return lines;
}

bool appendbuf(vector<char> &vbuffer, const char *buff, int sz, bool &lastChar, int &found, const int target)
{
  for (int i = sz - 1; i >= 0; i--)
  {
    if (buff[i] == '\n')
    {
      if (!lastChar)
        ++found;

      if (found == target)
        return true;
    }

    lastChar = false;
    vbuffer.push_back(buff[i]);
  }

  return false;
}

int main(int argc, char **argv) {

    if (argc != 3)
    {
      cerr << "Usage: " << argv[0] << " n file" << endl;
      return 1;
    }

    int count = atoi(argv[1]);
    if (count <= 0)
    {
      return 0;
    }

    string file = argv[2];

    ifstream ifs(file.c_str());

    ifs.seekg(0, ifs.end);

    int readsz = 100;
    char * buffer = new char[readsz];
    vector<char> vbuf;

    int found = 0;

    bool bof = false; // begin of file
    bool lastChar = true; // last character if newline shouldn't count as a line

    while (ifs && (found < count) && !bof)
    {
      int offset = static_cast<int>(ifs.tellg());
      if (offset >= readsz)
      {
        ifs.seekg(-1*readsz, ifs.cur);
        ifs.read (buffer, readsz);
        ifs.seekg(-1*readsz, ifs.cur);
      }
      else
      {
        readsz = static_cast<int>(offset) + 1;
        ifs.seekg(0, ifs.beg);
        ifs.read(buffer, readsz);
        bof = true;
      }

      if (appendbuf(vbuf, buffer, static_cast<int>(ifs.gcount()), lastChar, found, count))
      {
        cout << "Found " << found << " lines, done" << endl;
        break;
      }
      cout << "Found " << found << " lines" << endl;
    }

    for (int i = static_cast<int>(vbuf.size()) - 1; i >= 0; i--)
    {
      cout << vbuf[i]; // There should be newlines in the input 
    }

    delete [] buffer;
    return 0;
}
