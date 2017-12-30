#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void
printMap(const multimap<int, int> &numbers)
{
  for (std::multimap<int,int>::const_iterator it=numbers.begin(); it!=numbers.end(); ++it)
  {
    std::cout << (*it).first << " ";
  }
  cout << endl;
}

int main(int argc, char **argv)
{
  int k = 0;
  std::multimap<int, int> numbers;

  std::multimap<int,int>::iterator it=numbers.begin();
  std::multimap<int,int>::iterator mit=numbers.begin();
  for (int i = 1; i < argc; i++)
  {
    if (i == 1)
    {
      mit = numbers.begin();
    }

    it = numbers.insert(std::pair<int, int>(atoi(argv[i]), k++));
    if (numbers.size() % 2 == 0)
    {
      cout << "The median is now " << mit->first << endl;
      printMap(numbers);
      continue;
    }

    if (it->first < mit->first)
    {
      if (numbers.size() % 2 == 0)
      {
        --mit;
      }
    }
    //else if (it->first == mit->first)
    //{
    //}
    else 
    {
      if (numbers.size() % 2)
      {
        mit++;
      }
    }

    cout << "The median is now " << mit->first << "(" << mit->second << ")" << endl;
    printMap(numbers);
  }

  return 0;
}

