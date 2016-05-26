// Problem 10.9
// If there is a pointer to parents implement a inorder traversal
// without using extra space i.e. O(1)
// I.e. without using recursion or stack to save parents

#include "utils.h"

void printInorderO1Space(node *n)
{
    node *lastvisited = NULL;
    bool visitedLeft = false;
    bool visitedRight = false;

    string strVisited;
    while (n)
    {
        if (n->left && (lastvisited != n->left 
                    && lastvisited != n 
                    && lastvisited != n->right))
        {
            cout << "Going to " << n->val << " left subtree" << endl;
            n = n->left;
            continue;
        }
        else if ((n->left == NULL || lastvisited == n->left)
                && lastvisited != n && 
                (n->right == NULL || (lastvisited != n->right)))
        {
            cout << "Visiting " << n->val << " because left subtree "
                << "is null or already visited" << endl;

            if (strVisited.empty() == false)
            {
                strVisited += ",";
            }
            strVisited += n->val;
            cout << n->val << endl;
            lastvisited = n;
            continue;
        }
        else if (n->right && (lastvisited != n->right))
        {
            cout << "Going to " << n->val << " right subtree" << endl;
            n = n->right;
            continue;
        }
        else
        {
            cout << "Done visiting " << n->val << " subtree" << endl;
            lastvisited = n;
            n = n->parent;
            continue;
        }
    }

    cout << strVisited << endl;
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

    cout << "Printing tree inorder in O(1) space" << endl;
    printInorderO1Space(root);

    return 0;
}
