// 10.1 Find the successor
#include "utils.h"

node *findSuccessor2(node *n)
{
    if (n->parent && n->parent->right == n)
    {
        return findSuccessor2(n->parent);
    }
    else if (n->parent && n->parent->left == n)
    {
        return n->parent;
    }
    else if (n->parent == NULL)
    {
        return NULL;
    }
}

node *findSuccessor1(node *n)
{
    if (n->left)
    {
        return findSuccessor1(n->left);
    }
    else 
    {
        return n;
    }
}

node *findSuccessor(node *n)
{
    if (n == NULL)
    {
        return NULL;
    }

    // Find the leftmost successor of the right child
    // If this is the root then also find the leftmost successor of
    // the right child
    if (n->right)
    {
        findSuccessor1(n->right);
    }
    // I am the parent, if I have right child go find the right 
    // child's leftmost successor, if it is empty, we are done
    else if (n->parent == NULL) 
    {
        if (n->right)
        {
            return findSuccessor1(n->right);
        }
        else
        {
            return NULL;
        }
    }
    // I am the left child, so my parent is the successor
    else if (n->parent->left == n)
    {
        return n->parent;
    }
    else if (n->parent->right == n)
    {
        return findSuccessor2(n->parent);
    }
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

    // I am not bothering writing generic code to pass in the node 
    // for which we want to return the successor, just walk it in 
    // the code here based on a particular binary tree
    //node *curr = root->left->left->left->right->right->right;
    //node *curr = root->right->left->right;
    //node *curr = root->right;
    //node *curr = root;
    node *curr = root->right->left->left;
    node *successor = findSuccessor(curr);
    if (successor)
    {
        cout << "successor is " << successor->val << endl;
    }
    else
    {
        cout << "no successor" << endl;
    }

    return 0;
}
