#include "utils.h"

void
makeList(node *n, node *&lower, node *&higher)
{
  if ((n->left == NULL) && (n->right == NULL))
  {
    lower = n;
    higher = n;
    return;
  }

  if (n->left) 
  {
    node *l1 = NULL;
    node *h1 = NULL;
    makeList(n->left, l1, h1);
    h1->right = n;
    n->left = h1;
    lower = l1;
  }
  else
  {
    lower = n;
  }

  if (n->right) 
  {
    node *l2 = NULL;
    node *h2 = NULL;
    makeList(n->right, l2, h2);
    n->right = l2;
    l2->left = n;
    higher = h2;
  }
  else
  {
    higher = n;
  }

}

void
printList(node *head)
{
  cout << "Printing list forward" << endl;
  node *curr = head;

  node *tail = NULL;

  while (curr)
  {
    tail = curr;
    cout << curr->val << " ";
    curr = curr->right;
  }

  cout << endl;

  cout << "Printing list reverse" << endl;

  curr = tail;
  while (curr)
  {
    cout << curr->val << " ";
    curr = curr->left;
  }

  cout << endl;
}

int main(int argc, char **argv)
{
    // Find prev's successor in the inorder traversal of a binary tree
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " fileoftree " << endl;
        return -1;
    }
    node *root = readTree(argv[1]);

    node *lower = NULL;
    node *higher = NULL;
    makeList(root, lower, higher);

    printList(lower);
    return 0;
}
