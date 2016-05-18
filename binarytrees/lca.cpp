#include "utils.h"

bool foundA = false;
bool foundB = false;

node *lca = NULL;
size_t visited = 0;

void
findLCA(node *e, 
        const string &a,
        const string &b)
{
    if (e == NULL)
    {
        return;
    }

    ++visited;
    cout << "Visiting " << e->val << endl;

    if (foundA && foundB)
    {
        return;
    }

    bool foundAOrig = foundA;
    bool foundBOrig = foundB;

    findLCA(e->left, a, b);

    if (!foundAOrig && !foundBOrig && foundA && foundB && lca == NULL)
    {
        cout << "Setting lca to " << e->val << endl;
        lca = e;
        return;
    }

    findLCA(e->right, a, b);

    if (!foundAOrig && !foundBOrig && foundA && foundB && lca == NULL)
    {
        cout << "Setting lca to " << e->val << endl;
        lca = e;
        return;
    }

    if (e->val == a)
    {
        foundA = true;
        cout << "Found " << a << endl;
    }
    else if (e->val == b)
    {
        foundB = true;
        cout << "Found " << b << endl;
    }

}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " fileoftree a b" << endl;
        return -1;
    }
    node *root = readTree(argv[1]);

    string a = argv[2];
    string b = argv[3];

    cout << "Printing tree breadth first" << endl;
    printTreeBF(root);

    findLCA(root, a, b);

    cout << "LCA of " << a << " and " << b << " is " << lca->val << endl;
    cout << "Nodes visited " << visited << endl;

    return 0;
}
