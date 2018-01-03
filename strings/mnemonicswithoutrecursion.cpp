// 7.5 Compute all mnemonics for a phone number without using recursion
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <unordered_map>

using namespace std;

void makeMap(vector< string > &map)
{
  map.push_back("abc");
  map.push_back("def");
  map.push_back("ghi");
  map.push_back("jkl");
  map.push_back("mno");
  map.push_back("pqrs");
  map.push_back("tuv");
  map.push_back("wxyz");

    for (size_t i = 0; i < map.size(); i++)
    {
        cout << map[i] << endl;
    }
}

typedef struct SInfo
{
  char c;
  int keys;
  int runningIndex;
} sInfo;

void printNemonics(const string &number, const vector<string> &map)
{
  vector< sInfo > info;

  int nperms = 1;
  for (size_t i = 0; i < number.size(); i++)
  {
    nperms *= map[number[i] - '2'].size();

    sInfo node;
    node.c = number[i];
    node.keys = map[number[i] - '2'].size();
    node.runningIndex = 0;
    
    info.push_back(node);
    cout << "Level " << i << " has " << nperms << " branches" << endl;
  }

  cout << "Num permutations = " << nperms << endl;

  while (nperms--)
  {
    string str; // working set
    for (size_t i = 0; i < info.size(); i++)
    {
      char c = info[i].c; // '2', '3', ....
      int charIndex = info[i].runningIndex;
      str += map[c - '2'][charIndex];
    }
    cout << str << endl;

    // We start from the bottom of the tree and each level in the tree 
    // triggers a change in it's upper level
    for (int k = number.size()-1; k >= 0; k--)
    {
      sInfo &node = info[k];
      if (++node.runningIndex % node.keys)
      {
        break; // no need to go up the tree
      }

      node.runningIndex = 0; // reset
    }
  }

}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Please provide phone number" << endl;
        return 1;
    }

    string number = argv[1];
    vector< string > map;
    makeMap(map);

    string str;
    printNemonics(number, map);
    return 0;
}
