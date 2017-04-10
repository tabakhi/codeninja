// Check if a given tree is BST
// Note: We can also do this by doing an inorder traversal of the
// tree and then checking if the current value is > previous value
#include <vector>
#include <stdlib.h>
#include <climits>
#include "utils.h"
using std::vector;

bool check(node *curr, int &smin, int &smax)
{
  cout << "Checking node " << curr->ival << endl;

  if (curr == NULL)
  {
    return true;
  }

  // leaf node is always a BST by itself
  if (curr->left == NULL && curr->right == NULL)
  {
    cout <<"is a leaf node" << endl;
    smin = curr->ival;
    smax = curr->ival;
    return true;
  }

  int lsmin = 0;
  int lsmax = 0;
  int rsmin = 0;
  int rsmax = 0;

  if (curr->left)
  {
    bool rc = check(curr->left, lsmin, lsmax);
    cout << "left subtree min = " << lsmin <<
      " max = " << lsmax << " and subtree is bst: " <<
      rc << endl;

    if (!rc)
      return false;

    if (lsmin >= curr->ival)
      return false;

    if (lsmax >= curr->ival)
      return false;
  }

  if (curr->right)
  {
    bool rc = check(curr->right, rsmin, rsmax);
    cout << "right subtree min = " << rsmin <<
      " max = " << rsmax << " and subtree is bst: " <<
      rc << endl;

    if (!rc)
      return false;

    if (rsmax <= curr->ival)
      return false;

    if (rsmin <= curr->ival)
      return false;
  }

  if (curr->left)
  {
    smin = std::min(lsmin, curr->ival);
  }
  else
  {
    smin = curr->ival;
  }
  if (curr->right)
  {
    smax = std::max(rsmax, curr->ival);
  }
  else
  {
    smax = curr->ival;
  }

  return true;
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " fileoftree " << endl;
    return -1;
  }
  node *root = readTree(argv[1]);

  int smin = 0;
  int smax = 0;
  cout << "Checking if bst..." << endl;
  bool isbst = check(root, smin, smax);

  cout << "bst = " << isbst << endl;

  return 0;
}
