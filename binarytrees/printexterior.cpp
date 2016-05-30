// Problem 10.15: Compute the exterior of a binary tree
#include "utils.h"

bool onEdge = true;

// Only traverse the left subtree rooted at the root
void printLeft(node *root)
{
    cout << "Invoking printLeft on " << root->val << " (onEdge = " <<
        onEdge << ")" << endl;

    if (onEdge && (root->left || root->right))
    {
        cout << root->val << endl;
    }

    if (root->left)
    {
        printLeft(root->left);
        onEdge = false;
    }

    if (root->right)
    {
        printLeft(root->right);
    }
}

// Only traverse the right subtree rooted at the root
void printRight(node *root)
{
    cout << "Invoking printRight on " << root->val << " (onEdge = " <<
        onEdge << ")" << endl;

    if (root->right)
    {
        printRight(root->right);
    }

    if (!onEdge &&root->left)
    {
        printRight(root->left);
    }

    if (onEdge == false && root->left == NULL && root->right == NULL)
    {
        onEdge = true;
    }

    if (onEdge && (root->left || root->right))
    {
        cout << root->val << endl;
    }
}

void printLeaves(node *root)
{
    if (root->left)
    {
        printLeaves(root->left);
    }

    if (root->left == NULL && root->right == NULL)
    {
        cout << root->val << endl;
    }

    if (root->right)
    {
        printLeaves(root->right);
    }
}

void printExterior(node *root)
{
    if (root)
    {
        // Avoid printing the root otherwise we will print it twice
        // when we visit the leaves
        if (root->left || root->right)
        {
            cout << root->val << endl;
        }

        // Change it to false when we come back from the first leaf
        onEdge = true;
        if (root->left)
        {
            printLeft(root->left);
        }

        printLeaves(root);

        // Initially it must be false and true only when we
        // visit the first leaf
        onEdge = false;
        if (root->right)
        {
            printRight(root->right);
        }
    }
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
