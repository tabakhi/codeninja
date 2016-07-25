// 10.1 Find the successor
#include "utils.h"

typedef struct ll
{
    ll(const string &str)
    : next(NULL),
    val(str)
    {
    }

    ll *next;
    string val;
} ll;

void printList(ll *head)
{
    cout << "Printing the list" << endl;
    while (head)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

ll *makeList(node *root, ll *&head, ll *&curr)
{
    if (root == NULL)
    {
        return NULL;
    }

    makeList(root->left, head, curr);
    if (root->left == NULL && root->right == NULL)
    {
        ll *tmp = new ll(root->val);

        if (head == NULL)
        {
            head = tmp;
            curr = head;
        }
        else
        {
            curr->next = tmp;
            curr = curr->next;
        }
    }
    makeList(root->right, head, curr);
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

    ll *head = NULL;
    ll *curr = NULL;

    makeList(root, head, curr);

    printList(head);

    return 0;
}
