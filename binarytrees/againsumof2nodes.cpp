// http://www.geeksforgeeks.org/find-a-pair-with-given-sum-in-bst/

#include <iostream>
#include "utils.h"

class inOrderIterator
{
 public:
  inOrderIterator(node *root, bool leftFirst):
  m_curr(root),
  m_root(root),
  m_leftFirst(leftFirst)
  {

  }

  node *next();
 
 private:
  node * m_curr;
  node * m_root;
  bool m_leftFirst;
  stack<node *> m_s;
};

node *
inOrderIterator::next()
{

  while (1)
  {
    if (m_curr) 
    {
      m_s.push(m_curr);
      m_curr = (m_leftFirst) ? m_curr->left : m_curr->right;
    }
    else if (!m_s.empty())
    {
      m_curr = m_s.top();
      m_s.pop();
      
      node *tmp = m_curr;
      m_curr = (m_leftFirst) ? m_curr->right : m_curr->left;

      return tmp;
    }
    else
    {
      return NULL;
    }
  }

}

bool findsum(node *root, const int sum)
{
  inOrderIterator iter1(root, true);
  inOrderIterator iter2(root, false);

  node *lcurr = NULL;
  node *rcurr = NULL;
  while (1)
  {
    if (!lcurr)
    {
      lcurr = iter1.next();
      if (!lcurr)
      {
        cout << "left node is null " << endl;
        return false;
      }
    }

    if (!rcurr)
    {
      rcurr = iter2.next();
      if (!rcurr)
      {
        cout << "right node is null " << endl;
        return false;
      }
    }
    
    if (lcurr == rcurr)
    {
      cout << "left and right nodes meet " << lcurr->val << endl;
      return false;
    }

    int csum = lcurr->ival + rcurr->ival;
    cout << "Sum of " << lcurr->ival << " and " << rcurr->ival <<
      " equals " << csum << endl;

    if (csum == sum)
    {
      cout << "sum is equal" << endl;
      return true;
    }
    else if (csum < sum)
    {
      cout << "sum is less so moving lhs " << lcurr->ival << endl;
      lcurr = NULL;
    }
    else
    {
      cout << "sum is greater so moving rhs " << rcurr->ival << endl;
      rcurr = NULL;
    }
  }
  
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " fileoftree" << 
        " sum" << endl;
        return -1;
    }
    node *root = readTree(argv[1]);

    cout << "Printing tree breadth first" << endl;
    printTreeBF(root);

    const uint32_t sum = atoi(argv[2]);
    findsum(root, sum);
    return 0;
}
