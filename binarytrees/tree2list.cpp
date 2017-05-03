// Problem 15.12
// Convert a BST to a sorted linked list without using any
// extra storage
#include <vector>
#include <stdlib.h>
#include "utils.h"

using std::vector;

void
printLL(node *head)
{
  node *curr = head;
  node *prev = NULL;

  while (curr)
  {
    cout << curr->val << " ";

    prev = curr;
    curr = curr->right;
  }

  cout << endl;
  
  curr = prev; // The tail
  while (curr)
  {
    cout << curr->val << " ";
    curr = curr->left;
  }

  cout << endl;
}

// tmax, tmin => the max, the min
void
convert2 (node *root, node *& tmax, node *& tmin, node *& head)
{
  if (root->left == NULL && root->right == NULL)
  {
    // First leaf encountered is the head of the LL
    if (head == NULL)
    {
      head = root;
    }

    tmax = root;
    tmin = root;

    return;
  }

  node *lmax, *lmin;
  node *rmax, *rmin;

  if (root->left)
  {
    convert2(root->left, lmax, lmin, head);
    root->left = lmax;
    lmax->right = root;
  }

  if (root->right) 
  {
    convert2(root->right, rmax, rmin, head);
    root->right = rmin;
    rmin->left = root;
  }

  tmax = (root->right) ? rmax : root;
  tmin = (root->left) ? lmin : root;
}

node *
convert(node *root)
{
  node *head = NULL;
  node *lmax, *rmin;
  convert2(root, lmax, rmin, head);

  return head;
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " fileoftree " << endl;
        return -1;
    }
    node *root = readTree(argv[1]);

    printTreeBF(root);

    node *head = convert(root);
    printLL(head);

    return 0;
}
