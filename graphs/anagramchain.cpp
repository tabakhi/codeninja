// https://www.careercup.com/question?id=5684918990405632
#include <inttypes.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool
transformImpl(const string &s1,
    const string &s2,
    size_t index,
    vector<string> &path,
    unordered_map<string, string> &added)
{
  cout << __FUNCTION__ << " " << s1 << endl;
#if 0
  if (s1 == s2)
  {
    return true;
  }

  string s = s1;
  for (size_t i = index; i < s.size() - 1; i++)
  {
    swap(s[i], s[i+1]);
    if (added.find(s) == added.end())
    {
      added.insert(s);
      if (transformImpl(s, s2, i, path, added))
      {
        path.push_back(s);
        return true;
      }
      added.erase(s);
    }
    swap(s[i], s[i+1]);
  }
#endif

  queue<string> q;
  q.push(s1);
  added[s1] = "";

  while (!q.empty())
  {
    string s = q.front();
    q.pop();

    if (s == s2)
      return true;

    const string sOrig = s;
    for (size_t i = 0; i < s.size() - 1; i++)
    {
      swap(s[i], s[i+1]);
      if (added.find(s) == added.end())
      {
        q.push(s);
        added[s] = sOrig;
      }
      swap(s[i], s[i+1]);
    }

  } // while loop

  return false;
}

bool
transform(const string &s1, const string &s2, vector<string> &path)
{
  unordered_map<string, string> added;
  //added.insert(s1);
  if(transformImpl(s1, s2, 0, path, added))
  {
    cout << "Path is possible" << endl;

    string next = s2;
    while (added[next] != "")
    {
      path.push_back(next);
      next = added[next];
    }
    path.push_back(next);

    return true;
  }
  cout << "Path is not possible" << endl;
  return false;
}

int main(int argc, char **argv)
{
  string s1 = argv[1];
  string s2 = argv[2];

  vector<string> path;
  transform(s1, s2, path);
  reverse(path.begin(), path.end());
  for (vector<string>::const_iterator it = path.begin(); it != path.end(); it++)
  {
    cout << *it << endl;
  }
  return 0;
}
