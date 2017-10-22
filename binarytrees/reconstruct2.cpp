// 15.6 Reconstruct a BST from it's preorder traversal
// This code is more efficient than reconstruct.cpp as it traverses
// each node only once
// The same code can also be written using recursion, that maybe 
// much cleaner
#include <assert.h>
#include <vector>
#include <stack>
#include "utils.h"

typedef struct nodeAux
{
  nodeAux()
  : m_hasLeftSubtree(false),
  m_root(false),
  m_lhsMax(0),
  m_n(NULL)
  {
  };

  bool m_hasLeftSubtree; // whether this is in any left subtree
  bool m_root; // whether this is root
  int  m_lhsMax; // defined only if m_hasLeftSubtree == true
  node *m_n;
} nodeAux;

string int2Str(const int iVal)
{
  std::ostringstream oss;
  oss << iVal;
  return oss.str();
}

int main(int argc, char **argv)
{
  std::vector<int> nodes;
  for (int i = 1; i < argc; i++)
  {
    nodes.push_back(atoi(argv[i]));
  }

  node *root = NULL;

  std::stack<nodeAux> parents;

  for (size_t i = 0; i < nodes.size(); i++)
  {
    cout << "Visting " << nodes[i] << endl;

    node *n = new node(int2Str(nodes[i]));
    nodeAux aux;

    if (root == NULL)
    {
      cout << "Adding root " << nodes[i] << endl;
      root = n;

      aux.m_hasLeftSubtree = false;
      aux.m_root    = true;
      aux.m_lhsMax  = false;
      aux.m_n       = root;
      
      parents.push(aux);
      continue;
    }

    if (nodes[i] < parents.top().m_n->ival)
    {
      assert( parents.top().m_n->left == NULL );
      parents.top().m_n->left = n;

      cout << "Adding " << nodes[i] << " as left node of " << 
        parents.top().m_n->ival << endl;

      aux.m_hasLeftSubtree = true;
      aux.m_lhsMax = parents.top().m_n->ival;
      aux.m_n = n;
      parents.push(aux);
    }
    else 
    {
      bool inserted = false;
      while (!inserted) 
      {
        if (parents.top().m_hasLeftSubtree && nodes[i] < parents.top().m_lhsMax)
        {
          assert( parents.top().m_n->right == NULL );
          parents.top().m_n->right = n;

          cout << "Adding " << nodes[i] << " as right node of " << 
            parents.top().m_n->ival << endl;

          aux.m_hasLeftSubtree = true;
          aux.m_lhsMax = parents.top().m_lhsMax;
          aux.m_n = n;
          parents.push(aux);

          inserted = true;
        }
        else if (parents.top().m_hasLeftSubtree == false)
        {
          assert( parents.top().m_n->right == NULL );
          parents.top().m_n->right = n;

          cout << "Adding " << nodes[i] << " as right node of " << 
            parents.top().m_n->ival << endl;

          aux.m_n = n;

          cout << "Popping " << parents.top().m_n->ival << endl;
          parents.pop();
          parents.push(aux);

          inserted = true;
        }
        else 
        {
          cout << "Popping " << parents.top().m_n->ival << endl;
          parents.pop();
        }
      }
    }

  }

  cout << "Printing tree in order" << endl;
  printTreeInOrder(root, true);
  return 0;
}
