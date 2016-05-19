// Problem 10.6
// All nodes represent binary number 0 or 1, 
// compute the sum of all numbers represented by the root to leaf 
// paths 

#include "utils.h"

uint32_t sumOfPaths(node *e, uint32_t current)
{
    if (!e)
    {
        return 0;
    }

    // Root is the MSB and the leaves are the LSBs
    // so we shift by 1 for each child and if child is 1
    // we also add 1.
    assert(e->val == "0" || e->val == "1");
    current <<= 1;
    if (e->val == "1")
    {
        ++current;
    }


    if (e->left == NULL && e->right == NULL)
    {
        return current;
    }

    return sumOfPaths(e->left, current) + sumOfPaths(e->right, current);
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

    uint32_t current = 0;
    uint32_t sum = sumOfPaths(root, current);
    cout << "Sum of root to leaf paths is " << sum << endl;

    return 0;
}
