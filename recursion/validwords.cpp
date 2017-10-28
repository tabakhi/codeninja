// https://www.careercup.com/question?id=3534579
// Are all words in a sentence valid
#include <climits>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_set>

using namespace std;

typedef std::unordered_set<std::string> Dictionary;
typedef std::unordered_set<std::string>::const_iterator DictIter;

bool isValid(const string &s, size_t offset, size_t level, const Dictionary &dict)
{
  cout << __FUNCTION__ << "(ENTRY:) " << "offset = " << offset << " level = " << level
    << endl;

  if (offset >= s.size())
  {
    return true;
  }

  // Try all words beginning at offset starting with 1..end of string
  size_t len = 1;
  string curr = s.substr(offset, len);

  bool valid = false;
  while (!valid && offset + len <= s.size())
  {
    cout << "Checking word " << curr << endl;
    if (dict.find(curr) != dict.end())
    {
      valid = isValid(s, offset + len, level + 1, dict);
      if (valid)
        break;
    }

    curr = s.substr(offset, ++len);
  }

  cout << __FUNCTION__ << "(EXIT:) " << "offset = " << offset << " level = " << level
    << endl;
  return valid;
}

int main(int argc, char **argv)
{
    Dictionary validwords (
      {
      "hell", 
      "hello", 
      "he", 
      "low", 
      "or", 
      "world",
      "i",
      "is",
      "it",
      "sit",
      "nice",
      "in",
      "her",
      "the",
      "house",
      "houses",
      "on",
      "street",
      "use",
      "eon",
      "son",
      "here"
      }
    );

    if (argc != 2)
    {
        cerr << "Please provide sentence (without spaces)" << endl;
        return -1;
    }

    string s = argv[1];

    // TODO: Sanity checking whether string has spaces

    bool valid = isValid(s, 0, 0, validwords);
    cout << "Sentence is " << (valid ? "valid" : "invalid") << endl;

    return 0;
}

