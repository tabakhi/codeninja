// Remove all spaces in the string
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

int main(int argc, char **argv) {

    if (argc != 2)
    {
      cerr << "Usage: " << argv[0] << " sentence with spaces" << endl;
      return 1;
    }

    string s= argv[1];

    size_t i = 0;
    size_t si = 0;
    for (i = 0; i < s.size(); i++)
    {
      if (!isspace(s[i]))
      {
        s[si++] = s[i];
      }
    }

    if (si < i)
    {
      for (; si < s.size(); si++)
      {
        s[si] = '*';
      }
    }

    cout << s << endl;

    return 0;
}
