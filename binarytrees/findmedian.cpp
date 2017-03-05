// Find the median of a BST
#include "utils.h"

void count(node *n, size_t &num)
{
  if (!n)
    return;

  count(n->left, num);
  ++num;
  count(n->right, num);
}

node * findkth(node *n, size_t &i, const size_t &k)
{
  if (!n)
    return NULL;

  node *found = findkth(n->left, i, k);
  if (found)
    return found;
  if (i++ == k)
    return n;
  return findkth(n->right, i, k);
}

int findmedian(node *root)
{
  if (!root)
  {
    cerr << "Tree is empty" << endl;
    return -1;
  }

  size_t numElements = 0;
  count(root, numElements);
  cout << "There are " << numElements << " elements in the tree" << endl;

  size_t i = 0;
  node *median = findkth(root, i, numElements/2);
  cout << "The median is " << median->val << endl;

}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " fileoftree " << endl;
        return -1;
    }

    node *root = readTree(argv[1]);
    findmedian(root);

    return 0;
}
