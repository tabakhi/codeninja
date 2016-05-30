// Problem 10.15: Compute the exterior of a binary tree
#include "utils.h"

// Only traverse the left subtree rooted at the root
// do a preorder traversal and avoid the leaves
void printLeft(node *root, string &strExterior)
{
    cout << "Invoking printLeft on " << root->val << endl;

    if ((root->left || root->right))
    {
        strExterior += ",";
        strExterior += root->val;
    }

    if (root->left)
    {
        printLeft(root->left, strExterior);
    }
    else if (root->right)
    {
        printLeft(root->right, strExterior);
    }
}

// Only traverse the right subtree rooted at the root
// do a postorder traversal and avoid the leaves
void printRight(node *root, string &strExterior)
{
    cout << "Invoking printRight on " << root->val << endl;

    if (root->right)
    {
        printRight(root->right, strExterior);
    }
    else if (root->left)
    {
        printRight(root->left, strExterior);
    }

    if ((root->left || root->right))
    {
        strExterior += ",";
        strExterior += root->val;
    }
}

void printLeaves(node *root, string &strExterior)
{
    if (root->left)
    {
        printLeaves(root->left, strExterior);
    }

    if (root->left == NULL && root->right == NULL)
    {
        strExterior += ",";
        strExterior += root->val;
    }

    if (root->right)
    {
        printLeaves(root->right, strExterior);
    }
}

void printExterior(node *root)
{
    string strExterior;

    if (root)
    {
        // Avoid printing the root otherwise we will print it twice
        // when we visit the leaves
        if (root->left || root->right)
        {
            strExterior += root->val;
        }

        if (root->left)
        {
            printLeft(root->left, strExterior);
        }

        printLeaves(root, strExterior);

        if (root->right)
        {
            printRight(root->right, strExterior);
        }
    }

    cout << strExterior << endl;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " fileoftree" << endl;
        return -1;
    }
    node *root = readTree(argv[1]);

    printExterior(root);

    return 0;
}
