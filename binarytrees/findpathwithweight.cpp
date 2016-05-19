// Problem 10.7
// All nodes represent a weight to reach it
// Find whether a path exists from root to any node with the 
// given weight
// Weights are non negative, i.e. >= 0

#include "utils.h"

uint32_t getWeight(const string& val)
{
    uint32_t n = 0;
    istringstream iss(val);
    iss >> n;

    return n;
}

// We do a preorder traversal because we have to add our
// weight to the path before descending the subtrees
node * findPath(node *e, uint32_t k, uint32_t curr)
{
    if (!e)
    {
        return NULL;
    }

    curr += getWeight(e->val);

    // Check if the sum of weights to this leaf == k
    if (e->left == NULL && e->right == NULL)
    {
        if (curr == k)
        {
            return e;
        }
    }

    if (curr > k)
    {
        return NULL;
    }

    // First traverse left subtree, then right subtree
    node *x = findPath(e->left, k, curr);
    if (!x)
    {
        x = findPath(e->right, k, curr);
    }

    return x;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " fileoftree weight" << endl;
        return -1;
    }
    node *root = readTree(argv[1]);
    uint32_t weight = atoi(argv[2]);

    cout << "Printing tree breadth first" << endl;
    printTreeBF(root);

    uint32_t current = 0;
    node *leaf = findPath(root, weight, 0);
    if (leaf)
    {
        cout << "Path to " << leaf->val << " has weight " << weight 
        << endl;
    }
    else
    {
        cout  << "No path to leaves has weight " << weight << endl;
    }

    return 0;
}
