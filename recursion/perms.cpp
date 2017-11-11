// Print all permutations in lexical order
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

// Add helper function to make sure it is called only if string 
// size is >= 2
void printperms(string &str, size_t i)
{
  cout << __FUNCTION__ << " i = " << i << endl;

  if (i == str.size() - 2)
  {
    cout << str << endl;
    swap(str[i], str[i+1]);
    cout << str << endl;
    swap(str[i], str[i+1]);
  }
  else
  {
    printperms(str, i+1);
    for (size_t j = i+1; j < str.size(); j++)
    {
      swap(str[i], str[j]);
      printperms(str, i+1);
      swap(str[i], str[j]);
    }
  }

}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " " << "string" << endl;
    return -1;
  }

  string str = argv[1];

  cout << "Printing permutations" << endl;
  printperms(str, 0);
  cout << "Printed permutations" << endl;

  cout << str << endl;
  return 0;
}

