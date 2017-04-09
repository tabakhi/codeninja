// Reconstruct a BST from it's preorder traversal
#include <vector>
#include <stdlib.h>
#include "utils.h"

using std::vector;

int main(int argc, char **argv)
{
  vector<int> numbers;
   
  for (int i = 1; i < argc; i++)
  {
    numbers.push_back( atoi(argv[i]) );
  }

  if (numbers.size() == 0)
  {
    return 0;
  }

  // First node is always the root in preorder traversal
  ostringstream oss;
  oss << numbers[0];
  string strVal = oss.str();
  node *root = new node(strVal);

  for (size_t i = 1; i < numbers.size(); i++)
  {
    insertSmart(root, numbers[i]);
  }

  cout << "Printing tree pre order" << endl;
  printTreePreOrder(root, true);
  cout << "Printing tree breadth first" << endl;
  printTreeBF(root);
  return 0;
}
