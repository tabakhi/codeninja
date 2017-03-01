// Find if the sum of 2 nodes in a BST equal to a given value
// Assume tree is fully balanced
// Code should run in O(n) time and O(h) space complexity 
// where h is the height of the tree
#include "utils.h"
#include <stack>

void printStack(const stack<node *> &s)
{
  stack<node *> s2 = s;

  while (s2.empty() == false)
  {
    node *p = s2.top();
    cout << p->val << endl;
    s2.pop();
  }
}

void preorder(node *n, stack<node *> &s, bool left)
{
  if (left)
  {
    if (n->left)
    {
      s.push(n->left);
      preorder(n->left, s, left);
    }
  }
  else
  {
    if (n->right)
    {
      s.push(n->right);
      preorder(n->right, s, left);
    }
  }
}

node * getNextRight(node *root, node *curr, stack<node *> &stack)
{
  if (curr->left)
  {
    stack.push(curr->left);
    node *next = curr->left->right;
    while (next)
    {
      stack.push(next);
      next = next->right;
    }
  }

  if (stack.empty() == false) 
  {
    node *next = stack.top();
    stack.pop();
    return next;
  }
  else 
  {
    // We are still in the right subtree
    if (atoi(curr->val.c_str()) > atoi(root->val.c_str()))
    {
      return root;
    }
    else if (curr == root)
    {
      node *next = curr->left->right;
      while (next)
      {
        stack.push(next);
        next = next->right;
      }
      if (stack.empty() == false) 
      {
        node *next = stack.top();
        stack.pop();
        return next;
      }
    }
  }
}

node * getNextLeft(node *root, node *curr, stack<node *> &stack)
{
  cout << "curr val " << curr->val << endl;
  if (curr->right)
  {
    cout << "getNextLeft: pushing right side to stack" << endl;
    stack.push(curr->right);
    node *next = curr->right->left;
    while (next)
    {
      stack.push(next);
      next = next->left;
    }
  }
  else 
  {
    cout << "Nothing on right side" << endl;
  }

  if (stack.empty() == false) 
  {
    cout << "getNextLeft: Getting from top of stack" << endl;
    node *next = stack.top();
    stack.pop();
    return next;
  }
  else 
  {
    // We are still in the left subtree
    if (atoi(curr->val.c_str()) < atoi(root->val.c_str()))
    {
      cout << "Returning root as left subtree exhausted" << endl;
      return root;
    }
    else if (curr == root)
    {
      node *next = curr->right->left;
      while (next)
      {
        stack.push(next);
        next = next->left;
      }
      if (stack.empty() == false) 
      {
        node *next = stack.top();
        stack.pop();
        return next;
      }
    }
  }
}

void findsum(node *root, int k)
{
  if (root == NULL || root->left == NULL || root->right == NULL)
  {
    cout << "Tree should have atleast 3 nodes " << endl;
    return;
  }
  stack<node *> lStack;
  stack<node *> rStack;

  preorder(root, lStack, true);
  preorder(root, rStack, false);

  cout << "Left stack is " << endl;
  printStack(lStack);
  cout << "Right stack is " << endl;
  printStack(rStack);

  int leftVal = 0;
  int rightVal = 0;

  node *lnode = lStack.top();
  lStack.pop();
  node *rnode = rStack.top();
  rStack.pop();

  while (true)
  {
    leftVal = atoi(lnode->val.c_str());
    rightVal = atoi(rnode->val.c_str());

    if (leftVal >= rightVal)
    {
      cout << "Both nodes met or crossed, bailing out" << endl;
      break;
    }

    cout << "Trying leftval = " << leftVal << " rightval = " << rightVal
      << endl;

    int sum = leftVal + rightVal;
    if (sum == k)
    {
      cout << "Found sum " << leftVal << " " << rightVal << endl;
      break;
    }
    // left side must be increased
    else if (sum < k)
    {
      cout << "Sum is less so using next left " << endl;
      lnode = getNextLeft(root, lnode, lStack);
    }
    else 
    {
      cout << "Sum is greater so using next right " << endl;
      rnode = getNextRight(root, rnode, rStack);
    }
  }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " fileoftree " << "sum " << endl;
        return -1;
    }
    node *root = readTree(argv[1]);

    int k = atoi(argv[2]);

    findsum(root, k);

    return 0;
}
