// Problem 15.10: Build a BST from a sorted array
#include <math.h>
#include "utils.h"

node *
makebst(const vector<int> &arr, size_t start, size_t end)
{
  cout << "start = " << start << " end = " << end << endl;
  if (end - start == 1)
  {
    cout << "Creating leaf node from " << arr[start] << endl;
    node *n = new node(arr[start]);
    return n;
  }
  else if (end == start)
  {
    cout << "end == start, returning null" << endl;
    return NULL;
  }

  size_t maxHeight = floor( log(end - start) / log (2) ) + 1;
  size_t maxNodes = (1 << maxHeight) - 1;
  size_t rootIndex = start + maxNodes / 2;

  cout << "Max height of BST of this size = " << maxHeight << endl;
  cout << "Max nodes of BST of this size = " << maxNodes << endl;
  cout << "Root index = " << rootIndex << " val = " << arr[rootIndex] << endl;

  node *n = new node(arr[rootIndex]);

  n->left = makebst(arr, start, rootIndex);
  n->right = makebst(arr, rootIndex + 1, end);

  return n;
}

int main(int argc, char **argv)
{
  std::vector<int> arr;
  for (int i = 1; i < argc; i++)
  {
    arr.push_back(atoi(argv[i]));
  }

  node *root = makebst(arr, 0, arr.size());
  cout << "Printing tree breadth first" << endl;
  printTreeBF(root);
  return 0;
}
