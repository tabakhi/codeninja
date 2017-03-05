// Iterative in-order traversal

#include "utils.h"
#include <stack>

void traverse(node *n)
{
  stack<node *> s;

  while (1)
  {
    if (n) 
    {
      s.push(n);
      n = n->left;
    }
    else if (!s.empty())
    {
      n = s.top();
      s.pop();
      
      cout << n->val << " " << endl;

      n = n->right;
    }
    else
    {
      break;
    }
  }

  cout << endl;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " fileoftree" << endl;
        return -1;
    }
    node *root = readTree(argv[1]);

    cout << "Printing tree breadth first" << endl;
    printTreeBF(root);

    cout << "Printing tree inorder " << endl;
    traverse(root);

    return 0;
}
